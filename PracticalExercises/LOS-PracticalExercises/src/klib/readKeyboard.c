/**
 * \file readKeyboard.c
 * \brief Contains higher level code facilitating reading input from keyboard
 * \date 09/09/16
 */

#include "../include/readKeyboard.h"


/**
 * \fn uint8_t kgetc();
 * \brief This function will allow reading one acsii char from the keyboard.
 * \return uint8_t, the character that was read in.
 */
uint8_t kgetc(){
    uint32_t scanCode = 0;
    uint8_t endChar = 0;

    // ktranslateScanCode returns 0 if scan code is not supported.
    // the loop is there to make sure we get a valid character.
    while (endChar == 0){
        scanCode = kreadKeyboard();
        endChar = ktranslateScanCode(scanCode);
    }
    return endChar;
}