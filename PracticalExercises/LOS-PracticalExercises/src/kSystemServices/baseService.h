/**
 * \file baseService.h
 * \brief This file contain code related to the main system call dispatcher
 * \date 09/09/16
 */

//
// Created by user on 09/09/16.
//

#ifndef LOS_BASESERVICE_H
#define LOS_BASESERVICE_H

#include "../include/types.h"

void systemCallHandler(uint32_t callNumber, uint32_t paramSize, uint32_t* param);

// Now for the system call numbers
#define SYSC_READ_KEYBOARD      0x01    // Will put the process in wait queue for keyboard input
#define SYSC_READ_CLOCK         0x02    // Read the clock counter and return it to calling process
#define SYSC_ACQUIRE_HEAP       0x03    // Acquire a new heap block and assign it to process
#define SYSC_RELEASE_HEAP       0x04    // Release an heap block (Called upon process termination only)
                                        // Manual call to this syscall can be possible but will destroy
                                        // part of the caller memory space.
#define SYSC_WRITE_SCREEN       0x05    // Output some data to screen
#define SYSC_YIELD              0x06    // Yield processor. This basically cause the scheduler to run.
#define SYSC_WAIT_ON_EVENT      0x07    // Allow a process to wait on an event of its choice
#define SYSC_TERMINATE_PROCESS  0x08    // Remove the calling process from the system

#endif //LOS_BASESERVICE_H
