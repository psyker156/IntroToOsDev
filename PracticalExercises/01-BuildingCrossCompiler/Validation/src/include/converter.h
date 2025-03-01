//
// Created by user on 12/08/16.
//

#ifndef LOS_CONVERTER_H
#define LOS_CONVERTER_H

#include "types.h"
#include "kerror.h"
#include "ktroubleshoot.h"

// String to numeric and numeric to string
int8_t katoi(char* input, uint32_t* OUT_result);
void kitoa(uint32_t input, char* OUT_str);

// 4 bits number to hex digit
char ksingleHexFromFourBitsNumber(uint8_t fourBitsNumber);
uint8_t kfourBitsNumberFromSingleHex(char singleHex);

#endif //LOS_CONVERTER_H
