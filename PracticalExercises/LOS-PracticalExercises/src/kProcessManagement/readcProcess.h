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

#ifndef LOS_READCPROCESS_H
#define LOS_READCPROCESS_H

#include "../kio/clock/clock.h"
#include "../include/print.h"
#include "../include/converter.h"
#include "../include/types.h"
#include "processManagement.h"


void readAndDisplayClockTick();

#endif //LOS_READCPROCESS_H
