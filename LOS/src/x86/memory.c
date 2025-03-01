/**
 * \file memory.c
 * \brief This file contains code related to x86 specific memory management
 * \date 21/08/16
 */

#include "memory.h"

/**
 * \fn void loadGDTR(uint32_t* gdtrBuffer)
 * \brief This allow loading of the GDTR register
 * \param uint32_t* gdtrBuffer, buffer containing the GDTR data
 * \return void
 *
 * This simply interfaces the assembly _loadGDTR in a way that
 * prevent using external functions.
 */
void loadGDTR(uint32_t* gdtrBuffer){
    _loadGDTR(gdtrBuffer);
}

/**
 * \fn void setupGDT()
 * \brief Setup LOS GDT
 * \return void
 */
void setupGDT(){
    uint32_t * base = (uint32_t*)GDT_BASE;

    // First we crate a code descriptor for ring 0
    segmentDescriptor segment0;     // Not to be used!!!
    segment0.segmentLimitLow = 0;
    segment0.baseAddressLow = 0;
    segment0.baseAddressMid = 0;
    segment0.baseAddressHigh = 0;
    segment0.flagsLow = 0;
    segment0.flagsHigh = 0;

    segmentDescriptor codeRing0;
    codeRing0.segmentLimitLow = 0xFFFF;
    codeRing0.baseAddressLow = 0x0000;
    codeRing0.baseAddressMid = 0x00;
    codeRing0.baseAddressHigh = 0x00;
    codeRing0.flagsLow = 0;
    codeRing0.flagsLow |= 0b1010;      // Type Code, execute + read
    codeRing0.flagsLow |= (0b1 << 4);  // S Flag, this is a code or data segment
    codeRing0.flagsLow |= (0b00 << 5); // Descriptor priv. level. 0 this is ring 0
    codeRing0.flagsLow |= (0b1 << 7);  // P Flag, the segment is in memory
    codeRing0.flagsHigh = 0;
    codeRing0.flagsHigh |= 0b1111;      // High part of segment limit
    codeRing0.flagsHigh |= (0b0 << 4);  // AVL - Undefined, available for os
    codeRing0.flagsHigh |= (0b0 << 5);  // L flag, LOS is 32 bits, L flag is for 64 bits
    codeRing0.flagsHigh |= (0b1 << 6);  // D/B, we are 32 bits
    codeRing0.flagsHigh |= (0b1 << 7);  // G flag, granularity is 4kb, we want the full 32 bits

    segmentDescriptor dataRing0;
    dataRing0.segmentLimitLow = 0xFFFF;
    dataRing0.baseAddressLow = 0x0000;
    dataRing0.baseAddressMid = 0x00;
    dataRing0.baseAddressHigh = 0x00;
    dataRing0.flagsLow = 0;
    dataRing0.flagsLow |= 0b0010;      // Type data, read + write
    dataRing0.flagsLow |= (0b1 << 4);  // S Flag, this is a code or data segment
    dataRing0.flagsLow |= (0b00 << 5); // Descriptor priv. level. 0 this is ring 0
    dataRing0.flagsLow |= (0b1 << 7);  // P Flag, the segment is in memory
    dataRing0.flagsHigh = 0;
    dataRing0.flagsHigh |= 0b1111;      // High part of segment limit
    dataRing0.flagsHigh |= (0b0 << 4);  // AVL - Undefined, available for os
    dataRing0.flagsHigh |= (0b0 << 5);  // L flag, LOS is 32 bits, L flag is for 64 bits
    dataRing0.flagsHigh |= (0b1 << 6);  // D/B, we are 32 bits
    dataRing0.flagsHigh |= (0b1 << 7);  // G flag, granularity is 4kb, we want the full 32 bits

    kmemcpy((uint8_t*)&segment0, (uint8_t*)(base + 0), sizeof(segmentDescriptor));
    kmemcpy((uint8_t*)&codeRing0, (uint8_t*)(base + 2), sizeof(segmentDescriptor));
    kmemcpy((uint8_t*)&dataRing0, (uint8_t*)(base + 4), sizeof(segmentDescriptor));

    // Here, both absolutely required descriptors should be good.
    // Time to set the GDTR
    struct _DTR gdtr;
    gdtr.base = GDT_BASE;
    gdtr.limit = sizeof(segmentDescriptor) * 3;     // We only have 2 descriptor in the table
    loadGDTR((uint32_t*)&gdtr);
}

/**
 * \fn void kinitiatePagingStructuresForBaseOS();
 * \brief
 * \return void
 *
 *
 */
void kinitiatePagingStructuresForBaseOS(){
    uint32_t cr3 = 0;
    uint32_t* pageDirectoryAddress = (uint32_t*)KERNEL_PDT;
    uint32_t kpde = 0;
    uint32_t *pageTableAddress = (uint32_t*)0;
    uint32_t *pageAddress = (uint32_t*)0;

    // The following code maps the first 8 megs of memory on identity mapping.
    // These are grouped into 2 directory entries.
    for (int j = 0; j < 3; j++) {
        pageTableAddress = (uint32_t *)(KERNEL_PDT + (PAGE_SIZE * (j + 1)));
        kpde = kbuildPDE(pageTableAddress, 0, 0, 0, 0, 0, 1, 1);
        *(pageDirectoryAddress + j) = kpde;   // Installs the PDE in memory
        // Now build page tables for this group of 4 megs of memory

        for (int i = 0; i < 1024; i++) {
            pageAddress = (uint32_t*)((i * PAGE_SIZE) + (j * 0x400000));   // Hex number here is 4 megs
            pageTableAddress[i] = kbuildPTE(pageAddress, 1, 0, 0, 0, 0, 0, 0, 1, 1);
        }
    }

    cr3 = kbuildCR3((uint32_t*)KERNEL_PDT, 0, 0);
    _setCR3(cr3);
    _activatePaging();
}

/**
 * \fn uint32_t kbuildCR3(uint32_t* pageDirectoryAddress, uint8_t pcd, uint8_t pwt);
 * \brief This function builds a CR3 as per user requirements
 * \param uint32_t* pageDirectoryAddress, physical address where to find the Page Directory
 * \param uint8_t pcd, page level cache disable, see x86 documentation for details
 * \param uint8_t pwt, page level write-through, see x86 documentation for details
 * \return uint32_t, a usable CR3 value
 */
uint32_t kbuildCR3(uint32_t* pageDirectoryAddress, uint8_t pcd, uint8_t pwt){
    uint32_t cr3 = 0;
    cr3 |= ((uint32_t)pageDirectoryAddress & 0xFFFFF000);
    cr3 |= (pcd & 0x01) << 4;
    cr3 |= (pwt & 0x01) << 3;
    return cr3;
}

/**
 * \fn uint32_t kbuildPDE(uint32_t* pageTableAddress, uint8_t ps, uint8_t a, uint8_t pcd, uint8_t pwt, uint8_t us, uint8_t rw, uint8_t p);
 * \brief This function builds a page directory entry as per user configuration
 * \param uint32_t* pageTableAddress, physical address where the page table referenced by this directory entry is located
 * \param uint8_t ps, if using 4 kbit page size this must be 0
 * \param uint8_t a, accessed bit, if 1 it indicate that the PDE has been accessed (normaly used for "swapping" mechanism)
 * \param uint8_t pcd, page level cache disable, see x86 documentation for details
 * \param uint8_t pwt, page level write-through bit, see x86 documentation for details
 * \param uint8_t us, user-supervisor, if 0 user mode access not allowed
 * \param uint8_t rw, read-write bit, if 0 write not allowed
 * \param uint8_t p, present bit, if this is 0 a page fault will occur if a reference is made to this PDE
 * \return uint32_t, a usable PDE as configured by the user
 *
 *
 */
uint32_t kbuildPDE(uint32_t* pageTableAddress, uint8_t ps, uint8_t a, uint8_t pcd, uint8_t pwt, uint8_t us, uint8_t rw, uint8_t p){
    uint32_t pde = 0;
    pde |= ((uint32_t)pageTableAddress & 0xFFFFF000);
    pde |= (ps & 0x01) << 7;
    pde |= (a & 0x01) << 5;
    pde |= (pcd & 0x01) << 4;
    pde |= (pwt & 0x01) << 3;
    pde |= (us & 0x01) << 2;
    pde |= (rw & 0x01) << 1;
    pde |= (p & 0x01) << 0;
    return pde;
}

/**
 * \fn uint32_t kbuildPTE(uint32_t* pageAddress, uint8_t g, uint8_t pat, uint8_t d, uint8_t a, uint8_t pcd, uint8_t pwt, uint8_t us, uint8_t rw, uint8_t p)
 * \brief This function builds a page table entry as configured by the user
 * \param uint32_t* pageAddress, the physical address of the page referenced by the PTE
 * \param uint8_t g, global bit, this indicates if the translation is global or not
 * \param uint8_t pat, PAT bit, see x86 documentation for details
 * \param uint8_t d, dirty bit, this indicates if the page referenced by the PTE has been written to
 * \param uint8_t a, accessed bit, if 1 it indicate that the PTE has been accessed (normaly used for "swapping" mechanism)
 * \param uint8_t pcd, page level cache disable, see x86 documentation for details
 * \param uint8_t pwt, page level write-through bit, see x86 documentation for details
 * \param uint8_t us, user-supervisor, if 0 user mode access not allowed
 * \param uint8_t rw, read-write bit, if 0 write not allowed
 * \param uint8_t p, present bit, if this is 0 a page fault will occur if a reference is made to this PDE
 * \return uint32_t, a usable PTE as configured by the user
 *
 *
 */
uint32_t kbuildPTE(uint32_t* pageAddress, uint8_t g, uint8_t pat, uint8_t d, uint8_t a, uint8_t pcd, uint8_t pwt, uint8_t us, uint8_t rw, uint8_t p){
    uint32_t pte = 0;
    pte |= ((uint32_t)pageAddress & 0xFFFFF000);
    pte |= (g & 0x01) << 8;
    pte |= (pat & 0x01) << 7;
    pte |= (d & 0x01) << 6;
    pte |= (a & 0x01) << 5;
    pte |= (pcd & 0x01) << 4;
    pte |= (pwt & 0x01) << 3;
    pte |= (us & 0x01) << 2;
    pte |= (rw & 0x01) << 1;
    pte |= (p & 0x01) << 0;
    return pte;
}