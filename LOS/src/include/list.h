/**
 * \file list.h
 * \brief Contains code to manage a simple list
 * \date 08/09/16
 *
 * It is important to note that this list is not responsible for its own
 * memory management. Calling code IS ALWAYS responsible for either
 * allocation or deallocation of memory.
 */

#ifndef LOS_LIST_H
#define LOS_LIST_H

#include "ktroubleshoot.h"
#include "types.h"

struct _listEntry{
    uint32_t* element;
    struct _listEntry* nextEntry;
};
typedef struct _listEntry listEntry;

void klistAddEntry(listEntry* entry, listEntry* list);
listEntry* klistRemoveFirstEntry(listEntry** list);
listEntry* klistRemoveLastEntry(listEntry** list);
listEntry* klistRemoveEntryAtIndex(listEntry** list, uint32_t index);
listEntry* kgetNextEntry(listEntry* list);

#endif //LOS_LIST_H
