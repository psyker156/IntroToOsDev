/**
 * \file buffer.c
 * \brief This contains buffer related code
 * \date 16/08/16
 *
 * This file contains buffer related code. String operations are also here
 * so are general (as in non memory management) memory operations.
 */

#include "../include/buffer.h"

/**
 * \fn uint32_t kstrlen(char* string)
 * \brief Calculate the length of a C string
 * \param char* string, a usable C string
 * \return uint32_t, length of string
 *
 * Calculate len of a C string leaving '\0' out
 */
uint32_t kstrlen(char* string){
    uint32_t len = 0;

    // TODO optimize this... Current approach is simplistic and unoptimized
    while (*string != '\0'){
        len++;
        string++;
    }

    return len;
}

/**
 * \fn void kstrcat(char* str1, char* str2, char* OUT_str, uint32_t size)
 * \brief This concatenate 2 strings into a provided buffer
 * \param char* str1, First string to be placed in the concatenation
 * \param char* str2, Second string to be place in the concatenation
 * \param char* OUT_str, The buffer where the concatenation is to happen
 * \param uint32_t size, The maximum size of the concatenation buffer
 * \return void
 *
 * Concatenate 2 strings to an output string.
 * Memory for output string has to be allocated by caller
 */
void kstrcat(char* str1, char* str2, char* OUT_str, uint32_t size){
    uint32_t str1len = kstrlen(str1);
    uint32_t str2len = kstrlen(str2);
    uint32_t outIterator = 0;

    size--;     // Make sure we have space for '\0'

    for (uint32_t i = 0; i < str1len && outIterator < size; i++, outIterator++){
        *(OUT_str + outIterator) = *(str1 + i);
    }

    for (uint32_t i = 0; i < str2len && outIterator < size; i++, outIterator++){
        *(OUT_str + outIterator) = *(str2 + i);
    }

    *(OUT_str + outIterator) = '\0';
}


/**
 * \fn void kmemcpy(uint8_t* src, uint8_t* dst, uint32_t size)
 * \brief This copies data from src to dst for a length equal to size
 * \param uint8_t* src, the source buffer for the copy
 * \param uint8_t* dst, destination buffer
 * \param uint32_t size, maximum possible size in dst buffer
 * \return void
 *
 * This copies data from src to dst for a length equal to size
 */
void kmemcpy(uint8_t* src, uint8_t* dst, uint32_t size){
    // TODO optimize this... Current approach is simplistic and unoptimized
    for (uint32_t i = 0; i < size; i++){
        *(dst + i) = *(src + i);
    }
}