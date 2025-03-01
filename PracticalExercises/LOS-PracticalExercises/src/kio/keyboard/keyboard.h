/**
 * \file keyboard.h
 * \brief Keyboard handling code
 * \date 09/09/16
 */

#ifndef LOS_KEYBOARD_H
#define LOS_KEYBOARD_H

#include "../../include/types.h"
#include "../../kProcessManagement/processManagement.h"
#include "../../include/converter.h"
#include "../../include/print.h"


/*
 * Special keys to be handled.
 */

#define F1_CODE     0x3b    // f1 keypress scan code
#define F2_CODE     0x3c    // f2 keypress scan code


/*
 * Function declaration
 */

void khandleKeyboard(uint32_t* eventData);
uint32_t kreadKeyboard();
uint8_t ktranslateScanCode(uint32_t scanCode);

#endif //LOS_KEYBOARD_H
