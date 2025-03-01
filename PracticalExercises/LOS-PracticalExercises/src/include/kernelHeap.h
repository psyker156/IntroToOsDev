//
// Created by user on 02/08/16.
//

#include "kerror.h"
#include "types.h"
#include "ktroubleshoot.h"

#ifndef LOS_EARLYHEAP_H
#define LOS_EARLYHEAP_H

void* kmalloc(uint32_t size);
int8_t kfree(void* freeBuffer);
void kinitHeap();
void kvalidateHeap();

#endif //LOS_EARLYHEAP_H
