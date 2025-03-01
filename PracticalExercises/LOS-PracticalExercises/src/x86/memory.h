/**
 * \file memory.h
 * \brief This file contains code related to x86 specific memory management
 * \date 21/08/16
 */

#ifndef LOS_MEMORY_H
#define LOS_MEMORY_H

#include "../include/buffer.h"
#include "../include/types.h"

/**
 * First part of the file defines GDT related code and data
 */

extern void _loadGDTR(uint32_t* gdtrBuffer);
void loadGDTR(uint32_t* gdtrBuffer);
void setupGDT();

struct _SegDesc{
    uint16_t segmentLimitLow;
    uint16_t baseAddressLow;
    uint8_t baseAddressMid;
    uint8_t flagsLow;
    uint8_t flagsHigh;
    uint8_t baseAddressHigh;
};
typedef struct _SegDesc segmentDescriptor;

struct _DTR{
    uint32_t base;
    uint32_t limit;
};

#define GDT_BASE 0x1000     // This is the address where GDT is to be built

/**
 * Second part of the file define paging related code
 */

void kinitiatePagingStructuresForBaseOS();
uint32_t kbuildCR3(uint32_t* pageDirectoryAddress, uint8_t pcd, uint8_t pwt);
uint32_t kbuildPDE(uint32_t* pageTableAddress, uint8_t ps, uint8_t a, uint8_t pcs, uint8_t pwt, uint8_t us, uint8_t rw, uint8_t p);
uint32_t kbuildPTE(uint32_t* pageAddress, uint8_t g, uint8_t pat, uint8_t d, uint8_t a, uint8_t pcd, uint8_t pwt, uint8_t us, uint8_t rw, uint8_t p);

extern void _setCR3(uint32_t cr3Value);
extern void _activatePaging();

#define KERNEL_PDT 0x100000     // Kernel Page Directory Table is at 1meg
#define PAGE_SIZE 0x1000

#endif //LOS_MEMORY_H
