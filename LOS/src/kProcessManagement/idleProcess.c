/**
 * \file idleProcess.c
 * \brief Code for the idle system process.
 * \date 09/09/16
 */

#include "idleProcess.h"

/**
 * \fn void idleProcess();
 * \brief A call to this function enters an endless hlt loop
 * \return This should never return.
 *
 * This function calls into an asm function that is an endless
 * hlt loop. This allow implementation of an "idle system process"
 * without using a busy loop.
 */
void idleProcess(){
    ksetupInterrupts(); // Configure and activate interrupts
    kprint("LOS - System state after Interrupt");
    printSystemState();
    _idleHalt();
}