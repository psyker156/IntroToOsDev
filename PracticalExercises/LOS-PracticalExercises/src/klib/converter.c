/**
 * \file converter.c
 * \brief Contains type conversion related code
 * \date 12/08/16
 */

#include "../include/converter.h"

/**
 * \fn int8_t katoi(char* str, uint32_t* OUT_result)
 * \brief Convert an hex string to a number
 * \param char* str, the hex string that needs to be converted
 * \param uint32_t* OUT_result, the result of the conversion
 * \return int8_t, GENERROR in case of invalid string GENSUCCESS otherwise
 *
 * Convert an hex string to a number. String has to be XXXXXXXX format.
 * At current time, validation is naive and incomplete.
 */
int8_t katoi(char* str, uint32_t* OUT_result){
    uint32_t result = 0;

    // TODO validation is incomplete... Make this better
    for (int i = 0; i < 8; i++){
        // Make sure we have only valid HEX digit
        if (str[i] < '0' || str[i] > 'F' || (str[i] > '9' && str[i] < 'A')){
            // This is an invalid digit
            return GENERROR;
        }
    }

    result |= kfourBitsNumberFromSingleHex(str[0]) << 28;
    result |= kfourBitsNumberFromSingleHex(str[1]) << 24;
    result |= kfourBitsNumberFromSingleHex(str[2]) << 20;
    result |= kfourBitsNumberFromSingleHex(str[3]) << 16;
    result |= kfourBitsNumberFromSingleHex(str[4]) << 12;
    result |= kfourBitsNumberFromSingleHex(str[5]) << 8;
    result |= kfourBitsNumberFromSingleHex(str[6]) << 4;
    result |= kfourBitsNumberFromSingleHex(str[7]);

    *OUT_result = result;

    return GENSUCCESS;
}

/**
 * \fn void kitoa(uint32_t input, char* OUT_str)
 * \brief Converts 32 bit int to prefix less hex (C) string
 * \param uint32_t input, 32 bits input integer to be converted
 * \param char* OUT_str, converted hex string
 * \return void
 *
 * This will convert 32 bits ints to prefix less hexadecimal.
 */
void kitoa(uint32_t input, char* OUT_str){
    OUT_str[0] = ksingleHexFromFourBitsNumber((input & 0xF0000000) >> 28);
    OUT_str[1] = ksingleHexFromFourBitsNumber((input & 0x0F000000) >> 24);
    OUT_str[2] = ksingleHexFromFourBitsNumber((input & 0x00F00000) >> 20);
    OUT_str[3] = ksingleHexFromFourBitsNumber((input & 0x000F0000) >> 16);
    OUT_str[4] = ksingleHexFromFourBitsNumber((input & 0x0000F000) >> 12);
    OUT_str[5] = ksingleHexFromFourBitsNumber((input & 0x00000F00) >> 8);
    OUT_str[6] = ksingleHexFromFourBitsNumber((input & 0x000000F0) >> 4);
    OUT_str[7] = ksingleHexFromFourBitsNumber((input & 0x0000000F));
    OUT_str[8] = '\0';
}

/**
 * \fn char ksingleHexFromFourBitsNumber(uint8_t fourBitsNumber)
 * \brief Convert a 4 bits number to the equivalent hex digit
 * \param uint8_t fourBitsNumber, an 8 bits number
 * \return char, the hex digit representing the number.
 *
 * This simply converts a 4 bits number to the equivalent
 * hex digit. The input is an 8 bits number. Take note that only the
 * lowest nibble will be kept. The highest is discarded when the function
 * enters.
 */
char ksingleHexFromFourBitsNumber(uint8_t fourBitsNumber){
    char digit;
    fourBitsNumber = 0x0F & fourBitsNumber;

    if (fourBitsNumber <= 9){
        digit = '0' + fourBitsNumber;
    }else{
        digit = 'A' + fourBitsNumber - 10;
    }
    return digit;
}

/**
 * \fn uint8_t kfourBitsNumberFromSingleHex(char singleHex)
 * \brief Get a 4 bits number from a single hex digit
 * \param char singleHex, the hex digit that will be converted
 * \return uint8_t
 *
 * This will convert an hexadecimal digit to a 4 bits number
 * Note that this function is NOT SAFE. It assumes that
 * it will be correctly called using an (uppercase) hex digit.
 */
uint8_t kfourBitsNumberFromSingleHex(char singleHex){
    uint8_t fourBitsNumber;

    if (singleHex <= '9'){
        fourBitsNumber = singleHex - '0';
    }else{
        fourBitsNumber = singleHex - 'A' + 10;
    }
    return fourBitsNumber;
}