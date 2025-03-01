//
// Created by user on 16/08/16.
//

#ifndef LOS_STRING_H
#define LOS_STRING_H

#include "types.h"

uint32_t kstrlen(char* string);
void kstrcat(char* str1, char* str2, char* OUT_str, uint32_t size);
void kmemcpy(uint8_t* src, uint8_t* dst, uint32_t size);

#endif //LOS_STRING_H
