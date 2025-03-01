/**
 * \file kProcess.h
 * \brief Contains process management related code
 * \date 08/09/16
 */

#ifndef LOS_KPROCESS_H
#define LOS_KPROCESS_H

#include "idleProcess.h"
#include "readkProcess.h"
#include "readcProcess.h"
#include "../include/types.h"
#include "../include/kernelHeap.h"
#include "../include/kerror.h"
#include "../include/ktroubleshoot.h"
#include "../include/list.h"


/*
 * LOS process management constants.
 */

#define LOS_MAX_PROCESS 0x100
#define LOS_EMPTY_PROCESS   0x0
#define IDLE_PROCESS_PID    0x0

// In LOS, process can only wait on 2 events: Keyboard and Clock
// event from 0x0 to 0x1F are reserved for the system. Events from 0x20 to 0xFF
// would be available for future use (likely synchronisation???)
#define EVENT_CLOCK         0x00    // Queue number for clock waiting process
#define EVENT_KEYBOARD      0x01    // Queue number for keyboard waiting process

#define RESERVED_EVENT_UPPER_LIMIT      0x20    // 32
#define AVAILABLE_EVENT_UPPER_LIMIT     0x100   // 256

#define DEFAULT_TIME_SLICE  0x02    // How many tick can happen before preemption
#define DEFAULT_STACK_SIZE  0x400   // 1 k bytes of stack should be enough for now


/*
 * LOS process structure
 */

struct _process{
    uint8_t pid;                    // Process identifier
    uint32_t stack;                 // Pointer to the process stack - Storage for the running stack
    uint32_t heaps[4];              // Array of available heaps for a process
    uint32_t* eventReceiver;        // This is used when the process is stuck waiting
    uint32_t timeSlice;             // How many tick left before preemption
    uint8_t lock;                   // Lock variable used to synchronise access to process structure
    BOOL priority;                  // Only two level here 0 = least important, 1 = most important
                                    // In LOS, this is only used to prevent the idle process from
                                    // running if other processes are available.
    BOOL userMode;                  // Is the process a user mode or kernel mode process
    uint32_t* startAddress;         // Process entry point
    uint32_t* startStackAddress;    // Storage for initial stack pointer, used to clear the stack after execution.
};
typedef struct _process process;


/*
 * LOS process management global variables
 */

process* runningProcess;                    // Pointer to the currently running process
process* processArray[LOS_MAX_PROCESS];     // This array holds all process on the system no matter what their state is
                                            // in LOS, the PID of a processes is essentially the process offset within
                                            // the process array.
listEntry *readyQueue;                      // This is a list of all process that are ready to run

listEntry* eventsWaitQueues[AVAILABLE_EVENT_UPPER_LIMIT];   // Array of wait queues
                                                            // Each array element holds a list of process
                                                            // waiting on a specific event.


/*
 * LOS process management functions
 */
void dispatchEventToWaitingProcesses(uint32_t eventType, uint32_t* eventData);
void waitForEvent(uint32_t eventType, uint32_t* eventReceiver);
void addProcessToReadyQueue(process* readyProcess);
void runScheduler(BOOL addToReadyQueue);
process* createProcess(BOOL initStack,BOOL withHeap, BOOL userMode, BOOL priority, uint32_t* startAddress);
void initializeStackForNewKernelModeProcess(process* process);
process* initializeIdleProcess();
void initializeLOSBaseProcesses();
void initializeProcessArray();
void initializeWaitQueues();
int32_t reservePidForNewProcess();
void releasePID(uint32_t pidToBeReleased);

/*
 * LOS process management functions
 * These are all external function written in assembly.
 */
extern uint32_t _getUsableStackPointer();                                       // This is in ASMprocessManagement.asm
extern void _switchStack(uint32_t newStack, uint32_t* previousProcessStack);    // This is in ASMprocessManagement.asm
extern void _schedulerReturn();                 // NOT TO BE CALLED!!!!! This is used as a function pointer
                                                // when new process are initialized. See ASMinterrupt.asm
                                                // for details on this one.


#endif //LOS_KPROCESS_H
