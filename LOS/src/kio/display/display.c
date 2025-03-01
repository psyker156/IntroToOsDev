/**
 * \file display.c
 * \brief This contains display related code
 * \date 02/08/16
 *
 * This file contains display related code. While these functions
 * can be called directly by a user, they are intended to be used
 * by "interfacing" code created to limit their usage.
 */

#include "display.h"

/**
 * \fn void disp_clear()
 * \brief Clears the display
 *
 * This function will clear the display by replacing all
 * characters with a whitespace. Normally, a char in the
 * screen buffer is a 16 bits color + code int. This function
 * try writing 2 char at the same time in order to make
 * this process faster
 */
void disp_clear(){
    uint32_t *screenBuffer = (uint32_t*)SCREEN_BUFFER;
    uint32_t doubleScreenChar = buildDisplayChar(WHITESPACE, buildDisplayColor(WHITE, BLACK));
    doubleScreenChar |= doubleScreenChar << 16;

    // Time to print
    while (screenBuffer < (uint32_t*)(SCREEN_BUFFER + (COL * 2 * ROW))) {
        *screenBuffer = doubleScreenChar;
        ++screenBuffer;
    }
}

/**
 * \fn void disp_printLine(uint32_t* line)
 * \brief Print a correctly formated line to the display
 * \return void
 *
 * This simply print a line at the bottom of the screen.
 * Upper lines will be scrolled up by software. The line to be displayed
 * needs to be 80 * 16 bits long where each 16 bits bloc is in
 * XXCC format where XX is the color to be used and CC is the character
 * to be displayed.
 */
void disp_printLine(uint32_t* line){
    uint32_t *newLine = (uint32_t*)(SCREEN_BUFFER + (COL * 2 * (ROW - 1)));
    // Get an empty line
    disp_scrollUp();
    // Print the new line
    while (newLine < (uint32_t*)(SCREEN_BUFFER + (COL * 2 * ROW))){
        *newLine = *line;
        ++line;
        ++newLine;
    }
}

/**
 * \fn disp_scrollUp()
 * \brief Simply scrool the display one line up.
 * \return void
 *
 * This will simply scroll the display one line up. Scrolling is
 * done in software.
 */
void disp_scrollUp(){
    uint32_t *screenBuffer = (uint32_t*)SCREEN_BUFFER;
    uint32_t *screenBufferCopyData = (uint32_t*)(SCREEN_BUFFER + COL * 2);
    uint32_t doubleScreenCharSpace = buildDisplayChar(WHITESPACE, buildDisplayColor(WHITE, BLACK));
    doubleScreenCharSpace |= doubleScreenCharSpace << 16;

    // Time to scroll!
    // - 1 on the next line because we want an empty last line
    while (screenBuffer < (uint32_t*)(SCREEN_BUFFER + (COL * 2 * (ROW - 1)))){
        *screenBuffer = *screenBufferCopyData;
        ++screenBuffer;
        ++screenBufferCopyData;
    }

    // Now get the last empty line
    while (screenBuffer < (uint32_t*)(SCREEN_BUFFER + (COL * 2 * ROW))){
        *screenBuffer = doubleScreenCharSpace;
        ++screenBuffer;
    }
}