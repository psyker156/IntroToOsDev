//
// Created by user on 02/08/16.
//

#ifndef LOS_KTROUBLESHOOT_H
#define LOS_KTROUBLESHOOT_H

#include "types.h"
#include "converter.h"
#include "print.h"
#include "../kio/display/display.h"
#include "../x86/systemState.h"

/*
 * Troubleshooting constants
 */

// Display constants used by panic.
#define COLS    80
#define SEC_LINE_START_POSITION 80
#define SPACER  60

// Subsystems panic code
#define KERNEL_HEAP     0xFF << 24
#define KERNEL_INIT     0xFE << 24
#define TROUBLESHOOTING 0xFD << 24
#define GENERAL         0xFC << 24
#define KERNEL_PROCESS  0xFB << 24
#define NO_PANIC_SYSTEM 0xAA << 24

// The following are panic code to be used when calling the "panic" function

// GENERAL error codes
#define LIST_MANIPULATION_ERROR         0x00000001

// HEAP error codes
#define BAD_HEAP                        0x00000001
#define HEAP_MANAGEMENT_ERROR           0x00000002
#define HEAP_EXHAUSTED                  0x00000003

// Process error codes
#define NO_MORE_PID                     0x00000001
#define RELEASE_PID_OUT_OF_BOUNDS       0x00000002
#define INVALID_PID_BEING_RELEASED      0X00000003

#define NOT_IMPLEMENTED                 0xFFFFFF

/*
 * Troubleshooting functions
 */

void displayException(uint8_t handlerSource);
void panic(uint32_t subsystemCode, uint32_t errorCode);
void nopanic();         // This is used for debug only...
void printSystemState();
extern void _stopLOS();
extern void* _getStackPointerForStackTrace();


#endif //LOS_KTROUBLESHOOT_H
