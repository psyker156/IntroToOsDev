/**
 * \file systemState.c
 * \brief Contains code required to acquire/inspect the system state
 * \date 17/08/16
 */

#include "systemState.h"

/**
 * \fn void getSystemState(systemState* state)
 * \brief Call to assembly _getSystemState function. This is a proxy function.
 * \param systemState* state, system state is returned in the structure.
 * \return void
 *
 * This simply interface the assembly _getSystemState in a way that
 * prevent using external functions. The system state structure is
 * defined in file systemState.h.
 */
void getSystemState(systemState* state){
    _getSystemState(state);
}

/**
 * \fn void getMemoryState(uint32_t* low, uint32_t* high)
 * \brief Call to assembly _getMemoryState function. This is a proxy function.
 * \param uint32_t* low, lower part of memory available space in kbytes
 * \param uint32_t* high, highest part of memory available space in kbytes
 * \return void
 *
 * This simply interfaces the assembly _getMemoryState in a way that
 * prevent using external functions. This function is not 100%
 * precise and memory map should be used instead of this. However
 * in order to keep the system simple, this is used in LOS.
 */
void getMemoryState(uint32_t* low, uint32_t* high){
    _getMemoryState(low, high);
}

/**
 * \fn uint32_t stateXX(systemState* state)
 * \brief Returns the state described by the XX part
 * \param systemState* state, the desired state is extracted from this structure
 * \return uint32_t, the extracted state
 *
 * The following functions all get a specific value based on register
 * and flag specified in the function name. See intel documentation
 * for more details on each flags.
 */
uint32_t stateCR0Paging(systemState* state){
    uint32_t paging = state->cr0 & 0x80000000;
    return paging;
}
uint32_t stateCR0CacheDisable(systemState* state){
    uint8_t cacheDisable = state->cr0 & 0x40000000;
    return cacheDisable;
}
uint32_t stateCR0NotWriteThrough(systemState* state){
    uint32_t noWriteThrough = state->cr0 & 0x20000000;
    return noWriteThrough;
}
uint32_t stateCR0WriteProtect(systemState* state){
    uint32_t writeProtect = state->cr0 & 0x00010000;
    return writeProtect;
}
uint32_t stateCR0Emulation(systemState* state){
    uint32_t emulation = state->cr0 & 0x00000004;
    return emulation;
}

uint32_t stateCR0Protection(systemState* state){
    uint32_t protection = state->cr0 & 0x01;
    return protection;
}

uint32_t stateCR4PageSizeExtension(systemState* state){
    uint32_t pageSizeExtension = state->cr4 & 0x00000010;
    return pageSizeExtension;
}

uint32_t stateEFLAGSInterruptEnable(systemState* state){
    uint32_t  interruptEnable = state->eflags & 0x200;
    return interruptEnable;
}

uint32_t stateGTDRBase(systemState* state){
    uint32_t  baseAddress = state->gdtr[0];
    return baseAddress;
}
uint32_t stateGTDRLimit(systemState* state){
    uint32_t  limit = state->gdtr[1] & 0xFFFF;
    return limit;
}

uint32_t stateIDTRBase(systemState* state){
    uint32_t  baseAddress = state->idtr[0];
    return baseAddress;
}
uint32_t stateIDTRLimit(systemState* state){
    uint32_t  limit = state->idtr[1] & 0xFFFF;
    return limit;
}