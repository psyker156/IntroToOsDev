/**
 * The code present in this file is not part of LOS
 * it is intended to be used to simulate the presence
 * of a kernel mode process. The function being the
 * entry point of the process.
 *
 * In this case, the "process" will read and display
 * any character that is typed in.
 *
 * \date 09/09/16
 */

#ifndef LOS_READKPROCESS_H
#define LOS_READKPROCESS_H

#include "../include/print.h"
#include "../include/readKeyboard.h"

void readAndDisplayKeyboardKey();

#endif //LOS_READKPROCESS_H
