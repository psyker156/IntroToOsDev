/**
 * The code present in this file is not part of LOS
 * it is intended to be used to simulate the presence
 * of a kernel mode process. The function being the
 * entry point of the process.
 *
 * In this case, the "process" will read and the number
 * of clock ticks at a certain interval.
 *
 * \date 11/09/16
 */

#include "readcProcess.h"


void readAndDisplayClockTick(){
    char displayTick[9];
    int curTickCount = 0;
    uint32_t eventR;

    while (1) {
        waitForEvent(EVENT_CLOCK,&eventR);
        curTickCount = getTickCount();
        if (curTickCount % 20 <= 5) {
            kitoa(curTickCount, displayTick);
            kprint(displayTick);
        }

    }
}