/**
 * \file clock.h
 * \brief Code related to the system clock
 * \date 09/09/16
 */

#ifndef LOS_CLOCK_H
#define LOS_CLOCK_H

#include "../../include/types.h"
#include "../../kProcessManagement/processManagement.h"

void khandleTick();
uint32_t getTickCount();

#endif //LOS_CLOCK_H
