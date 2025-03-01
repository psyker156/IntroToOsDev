/**
 * \file list.c
 * \brief Contains code to manage a simple list
 * \date 08/09/16
 */

#include "../include/list.h"

/**
 * \fn void kListAddElement(uint32_t* element, uint32_t* list);
 * \brief Add element at end of list
 * \param listEntry* element, element to add to the list
 * \param listEntry* list, the list that will be modifiec
 * \return void
 *
 * This funtion simply adds an element at the end of the list
 *
 * IMPORTANT: All list related functions DO NOT DEAL WITH THE MEMORY MANAGEMENT part of the work
 *            THE USER IS RESPONSIBLE OF HIS/HER OWN MEMORY MANAGEMENT!!!
 */
void klistAddEntry(listEntry* entry, listEntry* list){
    entry->nextEntry = 0;
    while (list->nextEntry != 0){
        list = list->nextEntry;
    }
    list->nextEntry = entry;
}

/**
 * \fn listEntry* kListRemoveFirstElement(uint32_t** list);
 * \brief Remove the first element of the list
 * \param listEntry** list the list requiring removal
 * \return listEntry* pointer to the removed item
 *
 * The funtion removes the first element of a list. A pointer to the removed item is returned
 * to the calling function so it can memory manage the removed item.
 *
 * IMPORTANT: All list related functions DO NOT DEAL WITH THE MEMORY MANAGEMENT part of the work
 *            THE USER IS RESPONSIBLE OF HIS/HER OWN MEMORY MANAGEMENT!!!
 */
listEntry* klistRemoveFirstEntry(listEntry** list){
    listEntry* firstItem = *list;
    *list = firstItem->nextEntry;
    return firstItem;
}

/**
 * \fn listEntry* kListRemoveLastElement(uint32_t** list);
 * \brief remove last entry on a list
 * \param listEntry** list the list requiring removal
 * \return listEntry*, the entry that was removed
 *
 * The funtion removes the last element of a list. A pointer to the removed item is returned
 * to the calling function so it can memory manage the removed item.
 *
 * IMPORTANT: All list related functions DO NOT DEAL WITH THE MEMORY MANAGEMENT part of the work
 *            THE USER IS RESPONSIBLE OF HIS/HER OWN MEMORY MANAGEMENT!!!
 */
listEntry* klistRemoveLastEntry(listEntry** list) {
    listEntry *previousEntry = 0;
    listEntry *currentEntry = *list;

    if (currentEntry != 0) {
        while (currentEntry->nextEntry != 0) {
            previousEntry = currentEntry;
            currentEntry = currentEntry->nextEntry;
        }
        // Here we have the two last elements
        if (previousEntry != 0){
            previousEntry->nextEntry = (listEntry *) 0;
        }
    }
    return currentEntry;
}

/**
 * \fn listEntry* klistRemoveEntryAtIndex(listEntry** list, uint32_t index);
 * \brief Remove a specific entry from the list
 * \param listEntry** list, the list from which the entry will be removed
 * \param uint32_t index, index where the entry is to be removed (start at 0)
 * \return listEntry*, the removed entry.
 *
 * Will remove an entry from the list at a specific index. Note that the index
 * starts at 0. If index goes past bound of the list, in current code version,
 * this will generate a kernel panic.
 *
 * IMPORTANT: All list related functions DO NOT DEAL WITH THE MEMORY MANAGEMENT part of the work
 *            THE USER IS RESPONSIBLE OF HIS/HER OWN MEMORY MANAGEMENT!!!
 */
listEntry* klistRemoveEntryAtIndex(listEntry** list, uint32_t index){
    listEntry* removedEntry = 0;
    if (index == 0){
        removedEntry = klistRemoveFirstEntry(list);
    }else{
        listEntry* previousEntry = 0;
        listEntry* currentEntry = *list;
        for (uint32_t i=0; i<=index; i++){
            if (currentEntry->nextEntry == 0){
                if (i == index){
                    // Last entry was the one to be removed
                    removedEntry = klistRemoveLastEntry(list);
                    break;
                }
                // If we are here, index is invalid...
                // TODO at a later time, this should be modified in order to handle the error
                panic(GENERAL, LIST_MANIPULATION_ERROR);
            }else if (i == index){
                // We have found the entry to remove
                removedEntry = currentEntry;
                previousEntry->nextEntry = currentEntry->nextEntry;
                break;
            }
            previousEntry = currentEntry;
            currentEntry = currentEntry->nextEntry;
        }
    }
    return removedEntry;
}

/**
 * \fn listEntry* kGetNextEntry(listEntry* list);
 * \brief This function simply return the entry following the input entry in a list
 * \param listEntry* list, the input list entry
 * \return listEntry*, a pointer to the next list entry or 0 if none available
 *
 * Returns the entry following the input entry.
 *
 * IMPORTANT: All list related functions DO NOT DEAL WITH THE MEMORY MANAGEMENT part of the work
 *            THE USER IS RESPONSIBLE OF HIS/HER OWN MEMORY MANAGEMENT!!!
 */
listEntry* kgetNextEntry(listEntry* list){
    return list->nextEntry;
}