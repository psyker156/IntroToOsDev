/**
 * \file clock.c
 * \brief Code related to the system clock
 * \date 09/09/16
 */

#include "clock.h"

static uint32_t tickCount = 0;

/**
 * \fn void khandleTick();
 * \brief define what happens each time a tick comes in
 * \return void
 *
 * In order this should
 * -Make sure the tick is registered
 * -Make sure the tick is advertised to process who could be waiting on it
 * -Decrement current process time slice
 * -If current process tick count is 0, run the scheduler
 */
void khandleTick(){
    ++tickCount;    // Make sure tick count is registered
    if (tickCount == 0xFFFFFFFF){
        tickCount = 0;
    }

    dispatchEventToWaitingProcesses(EVENT_CLOCK, 0);

    runningProcess->timeSlice--;

    // This HAS to be last in order to prevent multiple handling
    // of a single tick when process switching occurs.
    if (runningProcess->timeSlice == 0){
        // Time is up! let's run the scheduler!
        runScheduler(TRUE);
    }
}

/**
 * \fn uint32_t getTickCount();
 * \brief This is a getter interface to tickCount variable. Please use this to access the variable.
 * \return uint32_t, the tickcount value
 *
 * Used to access the tickCount variable. Please use this and nothing else to access (read) the variable
 * should you need access to the tickCount value outside of this module.
 */
uint32_t getTickCount(){
    return tickCount;
}