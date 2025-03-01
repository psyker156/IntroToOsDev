/**
 * \file keyboard.h
 * \brief Keyboard handling code. Code in this file is intended to be used by higher level
 *          function in order to implement complex functionnalities.
 * \date 09/09/16
 */

#include "keyboard.h"

/**
 * \fn void khandleKeyboard(uint32_t eventData);
 * \brief This funtion handles a keyboard input and dispatching
 * \param uint32_t eventData, in this case, a keyboard scan code
 * \return void
 *
 * This function only dispatch the event to processes. Real logic is in
 * dispatchEventToProcess function. This function realy exists only to
 * limit the use of OS constants in the assembly code and to help
 * in debugging the system. Much better performance could be gained
 * by removing this function and having the keyboard assembly handler
 * call dispatchEventToProcess directly.
 */
void khandleKeyboard(uint32_t* eventData){
    // The following commented code stays there for
    // debug purposes.
    //char charcode[9];
    //kitoa((uint32_t)eventData, charcode);
    //kprint("Received char code:");
    //kprint(charcode);

    dispatchEventToWaitingProcesses(EVENT_KEYBOARD, eventData);
}

/**
 * \fn uint32_t kreadKeyboard();
 * \brief will return the scan code a key that are pressed (or depressed) on the keyboard.
 * \return uint32_t, scan code for the key pressed or depressed.
 *
 * This function returns the scan code of pressed or depressed keys on the keyboard.
 * One important thing to be aware about this function is that it NEEDS TO BE CALLED
 * FROM WITHIN A PROCESS CONTEXT. This is because the calling process will be put
 * in wait state until a keypress is made by the user.
 */
uint32_t kreadKeyboard(){
    uint32_t scanCode = 0;

    // After this the process will be in wait state. When awaken,
    // the process will return on the line following the waitForEvent.
    waitForEvent(EVENT_KEYBOARD, runningProcess->eventReceiver);
    // Process is awake! We have a keypress!
    scanCode = (uint32_t)(runningProcess->eventReceiver);
    runningProcess->eventReceiver = 0;

    return scanCode;
}

/**
 * \fn uint8_t ktranslateScanCode(uint32_t scanCode);
 * \brief Translates a scan code into a supported character.
 * \return uint8_t, is a normal ascii char
 *
 * Translates a scan code into a supported character. For this function to return non 0, the
 * scan code must have a matching entry in the char map (see kio/keyboard/charMap.c for details).
 * If no matching is found, it will return 0.
 */
uint8_t ktranslateScanCode(uint32_t scanCode){
    uint8_t character = 0;
    if (scanCode < CHARMAP_SIZE){
        character = charMap[scanCode];
    }
    return character;
}