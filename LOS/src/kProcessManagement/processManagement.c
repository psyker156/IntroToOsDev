/**
 * \file kProcess.h
 * \brief Contains process management related code
 * \date 08/09/16
 */

#include "processManagement.h"

/**
 * \fn void dispatchEventToWaitingProcesses(uint32_t eventType, uint32_t* eventData);
 * \brief Put waiting process into the ready queue for a specific event.
 * \param uint32_t eventType, The type of the event for which process are to be placed in ready queue.
 * \param uint32_t* eventData, The data that needs to be transmited to the waiting processes
 * \return void
 *
 * When called, this function will traverse the wait queue for the specific event. For
 * each process in the queue, it will copy the eventData to the process. All process
 * will also be placed in the readyQueue in order to be scheduled next time
 * runScheduler is called.
 *
 * IMPORTANT: This function does not call runScheduler. The currently running process
 *            is allowed to finish its time slice before being placed either in
 *            wait or ready state.
 */

void dispatchEventToWaitingProcesses(uint32_t eventType, uint32_t* eventData){
    listEntry* waitQueue = eventsWaitQueues[eventType];
    listEntry* currentEntry = 0;

    while (waitQueue != 0){     // When waitQueue == 0, no process is waiting on this event anymore
        currentEntry = klistRemoveFirstEntry(&waitQueue);
        currentEntry->nextEntry = 0;
        ((process*)currentEntry->element)->eventReceiver = eventData;

        // Process is done waiting, add to ready queue
        addProcessToReadyQueue((process*)currentEntry->element);
        kfree(currentEntry);
    }

    // If we are here we are done dispatching event.
    // Reset the waitQueue for this event since no more events are waiting on it.
    eventsWaitQueues[eventType] = 0;

    // Do not call runScheduler!!!!
    // This is running as part of an interrupt or part of a process
    // in any case the running process is not done running!!!
}

/**
 * \fn void waitForEvent(uint32_t eventType, uint32_t* eventReceiver);
 * \brief Will place the running process in wait state on a specific event
 * \param uint32_t eventType, the event on which the process is to wait
 * \param uint32_t* eventReceiver, pointer to receiving buffer for the event
 * \return void
 *
 * A call to this function will put the running process in wait state for
 * the specified event.
 *
 * IMPORTANT:   This function DOES call runScheduler since the running
 *              process is no longer runnable at the end of this function
 */
void waitForEvent(uint32_t eventType, uint32_t* eventReceiver){
    listEntry* queueForEvent = eventsWaitQueues[eventType];
    listEntry* newEntry = kmalloc(sizeof(listEntry));

    runningProcess->eventReceiver = eventReceiver;
    newEntry->element = (uint32_t*)runningProcess;
    newEntry->nextEntry = 0;

    // Adding the process into the wait queue
    if (queueForEvent == 0){
        eventsWaitQueues[eventType] = newEntry;
    }else{
        klistAddEntry(newEntry, queueForEvent);
    }

    // Running process will be switched
    runScheduler(FALSE);
}

/**
 * \fn void addProcessToReadyQueue(process* readyProcess);
 * \brief This adds a process into the readyQueue
 * \param process* readyProcess, pointer to a process structure that is ready to run
 * \return void
 *
 * Use this function to put a process in ready state. DO NOT put a process
 * to ready state by manualy changing the readyQueue.
 */
void addProcessToReadyQueue(process* readyProcess){
    listEntry* newEntry = kmalloc(sizeof(listEntry));
    newEntry->element = (uint32_t*)readyProcess;
    newEntry->nextEntry = 0;
    if (readyQueue == 0){
        readyQueue = newEntry;
    }else{
        klistAddEntry(newEntry, readyQueue);
    }
}

/**
 * \fn void runScheduler(BOOL addToReadyQueue);
 * \brief This will switch the running process.
 * \param BOOL addToReadyQueue, indicate if the running process is to be added to the ready queue
 * \return void
 *
 * Scheduler is FIFO with the exception that the idle process will be
 * skipped if wait list is longer than only idle process. In its current form,
 * a logic bug exists in the scheduler FIFO policy. Can you spot the bug?
 *
 * NOTE:    the addToReadyQueue is of the most importance. If runScheduler is
 *          called as the result of a process being at the end of its time slice
 *          then the process would be ready to be run again. In this case
 *          the parameter should be TRUE.
 *          However, if the function is called for any other reasons, this would
 *          be because the process has been put into a wait queue. Which means that
 *          it absolutely CAN'T be added to the ready queue or the system would be
 *          in an inconsistent state.
 */
void runScheduler(BOOL addToReadyQueue){
    // Scheduler running, this means running process time slice = 0
    // Reset time slice! (even if process is sent to wait, reset)
    runningProcess->timeSlice = DEFAULT_TIME_SLICE;

    if (readyQueue == 0){
        // readyQueue is empty, this means idle process is the current running process
        // simply return to continue running current process
        return;
    }

    // Some process (other than idle process) are waiting. Pick a new process!
    // First! save a pointer to the current running process stack entry
    // This will be used to update the current process stack when the stack is switched.
    uint32_t* pointerToPreviousProcessStack = &(runningProcess->stack);

    // Then put the running process into the ready queue if required.
    // If runScheduler was called result of a process been put in wait state
    // do not add that process to the ready queue
    if (addToReadyQueue) {
        addProcessToReadyQueue(runningProcess);
    }

    // Now select a new running process
    runningProcess = 0;
    listEntry* start = readyQueue;
    int i = 0;
    while (runningProcess == 0){
        // First found process was there before! FIFO queue.
        if (((process*)(start->element))->priority == 0 && start->nextEntry != 0){
            // If next process in list has priority 0 and another process
            // is available, skip the process, the next one is more important!!
            start = start->nextEntry;
            i++;
        }else{
            // We found a suitable process.
            runningProcess = (process*)start->element;
            kfree(klistRemoveEntryAtIndex(&readyQueue, i));
        }
    }

    // Switch stack to new process stack! <-- Really this is where new process wakes up and the old one goes to "sleep"
    // Upon return from the next function call, the new process is running
    _switchStack(runningProcess->stack, pointerToPreviousProcessStack);

    return;
}

/**
 * \fn process* createProcess(BOOL initStack, BOOL withHeap, BOOL userMode, BOOL priority, uint32_t* startAddress);
 * \brief This creates a new process.
 * \param BOOL initStack, indicates if function is responsible to setup initial values on the stack
 * \param BOOL withHeap, indicates if an heap needs to be set for the new process
 * \param BOOL userMode, indicates if the process is a userMode process
 * \param BOOL priority, indicate the priority of the process.
 * \param uint32_t* startAddress, entry point for the new process
 * \return process*, a pointer to the newly created process.
 *
 * This function creates a new process and register the new process with the system.
 * When this returns, the new process is ready to be added to the readyQueue. It is however
 * the job of the calling process to add the newly created process into the readyQueue.
 *
 * IMPORTANT:   Process created by this function CAN'T be run directly. They also CAN'T
 *              be placed in a waitQueue directly. Processes created by this function
 *              are MEANT TO BE PLACE IN READY QUEUE.
 *              In order to have a process created by this function to be ran without
 *              the help of the scheduler, the user NEED TO DO THE STACK SETUP HIMSELF and
 *              to pass in initStack at FALSE.
 *
 * NOTE:        The priority parameter should always be TRUE. False is only used for the idle
 *              process. While nothing prevents a user from passing is FALSE, this could result
 *              in problems related to the scheduling algorithm.
 *              Have you found the bug yet? - See runScheduler for more details.
 */

process* createProcess(BOOL initStack, BOOL withHeap, BOOL userMode, BOOL priority, uint32_t* startAddress){
    process* newProcess = 0;        // Init 0 to avoid kmalloc in case reservePidForNewProcess fails
    uint32_t* stack = 0;            // Init 0 to avoid kmalloc in case reservePidForNewProcess fails
    int32_t newPid = reservePidForNewProcess();

    if (newPid == GENERROR){
        // Can't create process if no PIDs are available!
        return FALSE;
    }

    // We have a PID, we can do process setup
    newProcess = kmalloc(sizeof(process));
    stack = kmalloc(DEFAULT_STACK_SIZE);
    stack = (uint32_t*)((uint8_t*)stack + DEFAULT_STACK_SIZE - 4);  // Stack grows down! Not Up!

    if (!userMode) {
        // Only kernel mode process implemented for now...
        newProcess->pid = newPid;
        newProcess->timeSlice = DEFAULT_TIME_SLICE;
        newProcess->priority = priority;
        newProcess->userMode = userMode;
        newProcess->stack = (uint32_t)stack;
        newProcess->startStackAddress = stack;
        newProcess->startAddress = startAddress;

        // If caller requested that the stack values be initialized by the createProcess function
        if (initStack) {
            // This will put a bunch of values on the stack so that the process
            // will be able to be scheduled when it is first ran.
            initializeStackForNewKernelModeProcess(newProcess);
        }
    }else{
        // TODO implement user mode process
        // This is there to keep compiler happy
        withHeap = TRUE;
        withHeap += 1;
    }

    // Now register the process with the OS.
    processArray[newPid] = newProcess;

    // All process creation task are done, return.
    return newProcess;
}

/**
 * \fn void initializeStackForNewKernelModeProcess(process* process);
 * \brief This will initialize stack values for a specific process
 * \param process* process, pointer to the process that needs stack initialisation
 * \return void
 *
 * This function will put some values on the stack of a process. This is required
 * in order to "trick" the CPU into thinking that this process has been previously
 * running on the system. Mostly this allows for some return values to be placed
 * on the stack so that, when scheduler returns, the code of the process (startAddress)
 * will be running. The second return address is there to guide the execution
 * flow out of the nested function call (run scheduler is tipycaly called by another function)
 *
 * The way the stack is built here will allow the code flow to work as:
 * - stack is switched to this new process stack (end of runScheduler)
 * - at return (and of runScheduler), execution returns to _schedulerReturn (end of _handlerClock in ASMprocessMAnagement.asm)
 * - when _handlerClock returns, the execution then returns to (uint32_t)process->startAddress
 * - at the point the process code is running.
 *
 * Note:    This function could have been written in a much more performant way. However as in a lot
 *          of code inside LOS, performance was set aside in order to get code that is easier to understand.
 */
void initializeStackForNewKernelModeProcess(process* process){
    process->stack -= 4;
    *(uint32_t*)(process->stack) = 0x00000216;                      // EFLAGS value
    process->stack -= 4;
    *(uint32_t*)(process->stack) = 0x00000008;                      // CS segment
    process->stack -= 4;
    *(uint32_t*)(process->stack) = (uint32_t)process->startAddress; // return EIP value (process entry point)
    //Now for GPRs
    process->stack -= 4;
    *(uint32_t*)(process->stack) = 0;                               // Following is a bunch of GRP to simulate
    process->stack -= 4;                                            // the effect a pusha would have had on the stack
    *(uint32_t*)(process->stack) = 0;
    process->stack -= 4;
    *(uint32_t*)(process->stack) = 0;
    process->stack -= 4;
    *(uint32_t*)(process->stack) = 0;
    process->stack -= 4;
    *(uint32_t*)(process->stack) = 0;
    process->stack -= 4;
    *(uint32_t*)(process->stack) = 0;
    process->stack -= 4;
    *(uint32_t*)(process->stack) = 0;
    process->stack -= 4;
    *(uint32_t*)(process->stack) = 0;
    // Now for the return address into the handler
    process->stack -= 4;
    *(uint32_t*)(process->stack) = (uint32_t)_schedulerReturn;      // return EIP, this return right after the scheduler
    //Now for GPRs
    process->stack -= 4;
    *(uint32_t*)(process->stack) = 0;                               // Following is a bunch of GRP to simulate
    process->stack -= 4;                                            // the effect a pusha would have had on the stack
    *(uint32_t*)(process->stack) = 0;                               // this pusha equivalent could have been replaced
    process->stack -= 4;                                            // by something cleaner... However, in order to keep
    *(uint32_t*)(process->stack) = 0;                               // the code easy mostly to prevent mistakes,
    process->stack -= 4;                                            // since this is a training OS, decision was made to
    *(uint32_t*)(process->stack) = 0;                               // keep a pusha here. More performance could have
    process->stack -= 4;                                            // been gained by making this a bit cleaner.
    *(uint32_t*)(process->stack) = 0;
    process->stack -= 4;
    *(uint32_t*)(process->stack) = 0;
    process->stack -= 4;
    *(uint32_t*)(process->stack) = 0;
    process->stack -= 4;
    *(uint32_t*)(process->stack) = 0;
}

/**
 * \fn process* initializeIdleProcess();
 * \brief Special function wrapper that creates the system IdleProcess
 * \return process*, a pointer to the idleProcess ready to be put in running state
 *
 * LOS starts on the idleProcess. Because of this, the idleProcess IS NOT scheduled
 * when it first starts running. It is directly put in running state and the stack
 * switch will occur outside of the runScheduler function. Because of this, the
 * idleProcess needs a special initial stack that is different from other processes.
 */
process* initializeIdleProcess(){
    // Get the idle process running
    //uint32_t stack =  0x9000;     // This line stays here for debug if ever needed...
                                    // do not remove this line even if commented.

    // Creating a new process
    // Note the used of the first parameter (initStack) set to FALSE
    process* newProcess = createProcess(FALSE, FALSE, FALSE, FALSE, (uint32_t*)idleProcess);

    // Now creating stack values manually
    *(uint32_t*)(newProcess->stack) = (uint32_t)newProcess->startAddress;   // Return EIP address

    //Now for GPRs  -   see comments in initializeStackForNewKernelModeProcess if more details needed.
    newProcess->stack -= 4;
    *(uint32_t*)(newProcess->stack) = 0;
    newProcess->stack -= 4;
    *(uint32_t*)(newProcess->stack) = 0;
    newProcess->stack -= 4;
    *(uint32_t*)(newProcess->stack) = 0;
    newProcess->stack -= 4;
    *(uint32_t*)(newProcess->stack) = 0;
    newProcess->stack -= 4;
    *(uint32_t*)(newProcess->stack) = 0;
    newProcess->stack -= 4;
    *(uint32_t*)(newProcess->stack) = 0;
    newProcess->stack -= 4;
    *(uint32_t*)(newProcess->stack) = 0;
    newProcess->stack -= 4;
    *(uint32_t*)(newProcess->stack) = 0;

    // At this point, the process is ready.
    // execution could be switched to this process AS IS.

    return newProcess;
}

/**
 * \fn void initializeLOSBaseProcesses();
 * \brief Initialize the base processes required
 * \return void
 *
 * Creates all bases processes required for LOS to work. When this function
 * returns, LOS is ready to launch the idleProcess and let the scheduler do its job.
 */
void initializeLOSBaseProcesses(){
    // Get the idle process running
    process* newProcess = initializeIdleProcess();
    runningProcess = newProcess;            // LOS starts on idle process

    // Short block to init another process
    //uint32_t stack = 0x8000;  // This stays here if ever needed for debug
    newProcess = createProcess(TRUE, FALSE, FALSE, TRUE, (uint32_t*)readAndDisplayKeyboardKey);
    addProcessToReadyQueue(newProcess);

    // Short block to init another process
    //stack = 0x9f00;   // This stays here if ever needed for debug
    newProcess = createProcess(TRUE, FALSE, FALSE, TRUE, (uint32_t*)readAndDisplayClockTick);
    addProcessToReadyQueue(newProcess);

    // End of process initialisation
}

/**
 * \fn void initializeProcessArray();
 * \brief Make sure that every field in the processArray is set to 0 (an invalid process)
 * \return void
 */
void initializeProcessArray(){
    // All process slot are initialized to 0
    for (int i=0; i<LOS_MAX_PROCESS; i++){
        processArray[i] = LOS_EMPTY_PROCESS;
    }
}

/**
 * \fn void initializeWaitQueues();
 * \brief Make sure that every wait queues are set to 0
 * \return void
 *
 * This is required since no process should be waiting when LOS is launched.
 */
void initializeWaitQueues(){
    for (int i=0; i<AVAILABLE_EVENT_UPPER_LIMIT; i++){
        eventsWaitQueues[i] = LOS_EMPTY_PROCESS;
    }
}

/**
 * \fn int32_t reservePidForNewProcess();
 * \brief reserver a pid for a new process
 * \return int32_t, the pid for the new process or GENERROR if something went bad (no more pid available).
 *
 * A call to this function will reserve a pid for a new process. The caller has the
 * responsibility to register the new process with the system (adding the process to the processArray)
 * or to realease the pid. The pid HAS TO BE RELEASED WHEN NO LONGER REQUIRED!! Not releasing
 * the pid will result in "PID starvation" preventing new process from being created if LOS_MAX_PROCESS
 * is reached.
 */
int32_t reservePidForNewProcess(){
    int32_t availablePid = GENERROR;
    for (int i=0; i<LOS_MAX_PROCESS; i++){
        if (processArray[i] == LOS_EMPTY_PROCESS){
            availablePid = i;   // The pid number is the index inside processArray
            break;
        }
    }
    return availablePid;
}

/**
 * \fn void releasePID(uint32_t pidToBeReleased);
 * \brief Release a pid making it available again for new processes.
 * \return void
 *
 * This needs to be called when a PID is no longer required (when a process exits).
 * Not calliong thi will result in "PID starvation" preventing new process from being created if LOS_MAX_PROCESS
 * is reached. Note that calling a pid release with an invalid PID will cause a kernel panic.
 */
void releasePID(uint32_t pidToBeReleased){
    if (pidToBeReleased > 0 && pidToBeReleased < LOS_MAX_PROCESS){
        if (processArray[pidToBeReleased] == LOS_EMPTY_PROCESS){
            // The pid being release is within bounds but no
            // process found for the pid... System is in inconsistent state...
            panic(KERNEL_PROCESS, INVALID_PID_BEING_RELEASED);
        }else{
            processArray[pidToBeReleased] = LOS_EMPTY_PROCESS;
        }
    }else{
        // releasePID was not within normal bounds...
        // system appears to be in inconsistent state
        panic(KERNEL_PROCESS, RELEASE_PID_OUT_OF_BOUNDS);
    }
}