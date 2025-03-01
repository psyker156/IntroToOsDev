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
    // Important note, don't be afraid to change the order
    // of the task presented here. It is important, however,
    // that you follow the offsets for the segments since not
    // following these would result in trouble later on.

    // Create a NULL descriptor for offset 0 of the table

    // Create a ring 0 code descriptor for offset 8 of the table

    // Create a ring 0 data descriptor for offset 16 of the table

    // Copy all descriptors to their correct location in memory

    // Setup GDTR value

    // Call loadGDTR(uint32_t* gdtrBuffer) to activate the new
    // GDTR value and segments

}

/**
 * \fn void kinitiatePagingStructuresForBaseOS();
 * \brief
 * \return void
 *
 *
 */
void kinitiatePagingStructuresForBaseOS(){

    // Build paging related data structures

    // Build new CR3 value

    // Call _setCR3() to set new CR3 value

    // Call _activatePaging() to activate the paging mechanism

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