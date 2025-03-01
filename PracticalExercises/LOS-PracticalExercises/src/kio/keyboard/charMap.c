/**
 * \file charTable.h
 * \brief LOS char map
 * \date 09/09/16
 */

#include "charMap.h"

/**
 * \fn void initCharMap()
 * \brief Initialize the char map with code to char association.
 * \return void
 *
 * The current association will only map lower case letters and numbers.
 */
void kinitCharMap(){
    // Unhandled code are set to 0
    for (int i=0; i<256; i++){
        charMap[i] = 0;
    }

    // Only handle numbers and lower char for now...
    charMap[0x02] = '1';
    charMap[0x03] = '2';
    charMap[0x04] = '3';
    charMap[0x05] = '4';
    charMap[0x06] = '5';
    charMap[0x07] = '6';
    charMap[0x08] = '7';
    charMap[0x09] = '8';
    charMap[0x0a] = '9';
    charMap[0x0b] = '0';
    charMap[0x10] = 'q';
    charMap[0x11] = 'w';
    charMap[0x12] = 'e';
    charMap[0x13] = 'r';
    charMap[0x14] = 't';
    charMap[0x15] = 'y';
    charMap[0x16] = 'u';
    charMap[0x17] = 'i';
    charMap[0x18] = 'o';
    charMap[0x19] = 'p';
    charMap[0x1e] = 'a';
    charMap[0x1f] = 's';
    charMap[0x20] = 'd';
    charMap[0x21] = 'f';
    charMap[0x22] = 'g';
    charMap[0x23] = 'h';
    charMap[0x24] = 'j';
    charMap[0x25] = 'k';
    charMap[0x26] = 'l';
    charMap[0x2c] = 'z';
    charMap[0x2d] = 'x';
    charMap[0x2e] = 'c';
    charMap[0x2f] = 'v';
    charMap[0x30] = 'b';
    charMap[0x31] = 'n';
    charMap[0x32] = 'm';

}

