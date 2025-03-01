/**
 * \file print.c
 * \brief Contains user interface to display info to screen
 * \date 16/08/16
 */

#include "../include/print.h"

static void prepareStringForPrint(char* string, uint16_t* buffer);

/**
 * \fn void kprint(char* toBePrinted)
 * \brief Print a string to display
 * \param char* toBePrinted, the string to be printed
 * \return void
 *
 * Will print a string to the output scrolling the display
 * Maximum string len is equal to COL as defined in display
 */
void kprint(char* toBePrinted){
    uint16_t printBuffer[80];                           // Currently located on the stack for ease of development
    prepareStringForPrint(toBePrinted, printBuffer);
    disp_printLine((uint32_t*)printBuffer);             // Lower level print function
}


/**
 * \fn static void prepareStringForPrint(char* string, uint16_t* buffer)
 * \brief Translate a C string into a displayable format
 * \param char* string, the C string that needs to be translated
 * \param uint16_t* buffer, a buffer of 80 * 16 bytes to receive the displayable string
 * \return void
 *
 * This does the required preparation on the string and build a
 * displayable string to the OUT_buffer. Maximum input string
 * len in 80 chars. Overlong chars will be dropped.
 */
static void prepareStringForPrint(char* string, uint16_t* buffer){
    uint32_t inputLen = kstrlen(string);
    uint32_t i = 0;

    // If input is too long, truncate.
    if (inputLen > COL){
        inputLen = COL;
    }

    // Let the input begin the string
    while (i < inputLen){
        *(buffer + i) = buildDisplayChar(*(string + i), buildDisplayColor(WHITE, BLACK));
        i++;
    }

    // Fill the rest of the line with whitespaces
    while (i < COL){
        *(buffer + i) = buildDisplayChar(WHITESPACE, buildDisplayColor(WHITE, BLACK));
        i++;
    }
}