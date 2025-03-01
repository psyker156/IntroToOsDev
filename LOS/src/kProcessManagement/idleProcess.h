/**
 * \file idleProcess.h
 * \brief Code for the idle system process.
 * \date 09/09/16
 */

#ifndef LOS_IDDLEPROCESS_H

#include "../include/ktroubleshoot.h"
#include "../include/print.h"
#include "../x86/interrupt.h"

#define LOS_IDDLEPROCESS_H

/*
 * Function declaration
 */
void idleProcess();
extern void _idleHalt();    // This is an assembly written function (ASMHalt.asm for more details)

#endif //LOS_IDDLEPROCESS_H
