//
// Created by user on 17/08/16.
//

#ifndef LOS_SYSTEMSTATE_H
#define LOS_SYSTEMSTATE_H

#include "../include/converter.h"
#include "../include/print.h"
#include "../include/types.h"

struct _sState {         // Offset within structure
    uint32_t cr0;       // 0
    uint32_t cr1;       // 4  -  This is there but not used. See comment in ASMsystemState.asm
    uint32_t cr2;       // 8
    uint32_t cr3;       // 12
    uint32_t cr4;       // 16
    uint32_t eflags;    // 20
    uint32_t gdtr[2];   // 24
    uint32_t idtr[2];   // 28
};
typedef struct _sState systemState;

extern void _getSystemState(systemState* state);
void getSystemState(systemState* state);

extern void _getMemoryState(uint32_t* low, uint32_t* high);
void getMemoryState(uint32_t* low, uint32_t* high);

uint32_t stateCR0Paging(systemState* state);
uint32_t stateCR0CacheDisable(systemState* state);
uint32_t stateCR0NotWriteThrough(systemState* state);
uint32_t stateCR0WriteProtect(systemState* state);
uint32_t stateCR0Emulation(systemState* state);
uint32_t stateCR0Protection(systemState* state);

uint32_t stateCR4PageSizeExtension(systemState* state);

uint32_t stateEFLAGSInterruptEnable(systemState* state);

uint32_t stateGTDRBase(systemState* state);
uint32_t stateGTDRLimit(systemState* state);

uint32_t stateIDTRBase(systemState* state);
uint32_t stateIDTRLimit(systemState* state);

void printSystemState();

#endif //LOS_SYSTEMSTATE_H
