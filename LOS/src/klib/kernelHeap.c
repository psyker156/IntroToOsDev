/**
 * \file earlyHeap.c
 * \brief Contains code to manage an kernel heap
 * \date 02/08/16
 */

//
// Created by user on 02/08/16.
//

#include "../include/kernelHeap.h"

static int32_t kfindHeapBloc(int32_t nbloc);
static int8_t kreserveHeapBlock(int32_t startBlock, int32_t nbloc);
static void kreleaseHeapBlock(int32_t startBlock, int32_t nbloc);
static int8_t kfindStartBlockAndLengthForAddress(void* startAddress, int32_t* OUT_startBlock, int32_t* OUT_nblock);

extern uint32_t _kernelHeapArray;
extern uint32_t _kernelHeap;

uint8_t* kernelHeapArray = (uint8_t*)&_kernelHeapArray;
uint8_t* kernelHeap = (uint8_t*)&_kernelHeap;

static char kernelHeapIsUsable = 0;

/**
 * \fn void* kmalloc(uint32_t size)
 * \brief Allocate memory in kernel heap
 * \param uint32_t size, size of required allocation
 * \return void*, a pointer to the newly allocated buffer or 0 if no suitable memory bloc could be found
 *
 * This version of kmalloc will find the first
 * fit in a given heap. Returned as a void*.
 * The block of memory is 0 on heap init and when
 * memory is freed. Therefore, this function does not
 * set memory back to 0.
 *
 * The allocation is done defensively validating the correctness
 * of expected address. There should be 4KB of memory for the
 * kernelHeapArray
 *
 * This return 0 if no suitable bloc could be used
 */
// We need to prevent gcc from optimizing this particular function...
#pragma GCC push_options
#pragma GCC optimize ("O0")
void* kmalloc(uint32_t size) {

    void *returnPointer = 0;
    int32_t startBlockPosition;
    uint32_t unitsRequired;

    if (kernelHeapIsUsable) {

        // Following two lines uses boolean logic to avoid
        // a division/modulo operation
        unitsRequired = size >> 6;         // This heap works by 64 bytes increment
        // >> 6 here is like size / 64
        unitsRequired += (size & 0x3F) != 0;       // size & 0x3F is like size % 64
        // We have required data, now is time to prepare the allocation
        _acquireLock();
        startBlockPosition = kfindHeapBloc(unitsRequired);
        if (startBlockPosition != GENERROR) {
            if (kreserveHeapBlock(startBlockPosition, unitsRequired) == GENSUCCESS) {
                // All condition for allocation were meet with success
                // We now calculate the pointer address to be returned
                // using 64 since this is our heap resolution
                returnPointer = kernelHeap + (startBlockPosition * 64);
            }
        }else{
            panic(KERNEL_HEAP, HEAP_EXHAUSTED); // No suitable memory blocks were found
        }
        _releaseLock();
    }else{
        panic(KERNEL_HEAP, BAD_HEAP);       // Should not be here!
                                            // Since we are not sure if the heap
                                            // is usable, abort...
    }
    return returnPointer;
}
#pragma GCC pop_options
/**
 * \fn static int32_t kfindHeapBloc(int32_t nbloc)
 * \brief Find a suitable block in the heap
 * \param int32_t nbloc, number of contiguous memory block required
 * \return int32_t, the location of the first block or GENERROR if no suitable block was found
 *
 * This is the code that finds the bloc to be used
 * return GENERROR if no suitable bloc could be found.
 */
// We need to prevent gcc from optimizing this particular function...
#pragma GCC push_options
#pragma GCC optimize ("O0")
static int32_t kfindHeapBloc(int32_t nbloc){
    // We do not have a very big heap... Because of this
    // that algorithm avoid recursion.
    // Also no need to validate heap. This is only called by kmalloc
    // therefore, heap validation has already happened

    int16_t suitableBlocksFound = 0;
    int32_t startBlock= GENERROR;
    // Now scan heap array to set it to find sufficient contiguous memory
    for (uint16_t i=0; i < (4096 * 4); i++){
        if (*(kernelHeapArray + i) == 0){
            ++suitableBlocksFound;
            if (startBlock == GENERROR){
                startBlock = i;
            }
            if (suitableBlocksFound == nbloc){
                // We have enough blocks
                break;
            }
        }else{
            // Non contiguous memory, reset this stuff back to 0
            suitableBlocksFound = 0;
            startBlock = GENERROR;
        }
    }

    // Validate before return that we have enough memory
    // This is because an inconsistent state could be created if
    // startBlock is near the end of the buffer and nbloc
    // overflows the heap boundary.
    if (suitableBlocksFound != nbloc){
        startBlock = GENERROR;
    }

    return startBlock;
}
#pragma GCC pop_options
/**
 * \fn static int8_t kreserveHeapBlock(int32_t startBlock, int32_t nbloc)
 * \brief Reserver a block in the heap allocation array
 * \param int32_t startBlock, first block of the reservation
 * \param int32_t nbloc, number of block to be reserved
 * \return int8_t, GENSUCCESS if reservatio succeded GENERROR otherwise
 *
 * This will modify the heap allocation array in order to
 * reflect a new allocation of memory. This should only
 * be called after kfindHeapBloc. Doing otherwise is unsafe.
 */
static int8_t kreserveHeapBlock(int32_t startBlock, int32_t nbloc){
    // Validate that the start block and nbloc are not going out
    // of bound for our memory array
    if ((startBlock + nbloc -1) > (4096 * 4) || startBlock > (4096 * 4)){
        // This allocation is invalid!!!
        return GENERROR;
    }

    // The first block tells how many block there are
    // in this specific allocation
    *(kernelHeapArray + startBlock) = nbloc;

    for (int i=1; i < nbloc; i++){  // Here i = 1 since the first bloc is allocated
                                    // at the previous line
        // A block set at 0xFF means that it is not sovereign for it's own
        // allocation. It is dependent on another block. This also means
        // that the maximum allocation possible under this heap
        // is 64 * 0xFE = 16256 bytes. Should be enough for an early heap...
        *(kernelHeapArray + startBlock + i) = 0xFF;
    }

    return GENSUCCESS;
}

/**
 * \fn static int8_t kfindStartBlockAndLengthForAddress(void* startAddress, int32_t* OUT_startBlock, int32_t* OUT_nblock)
 * \brief Find the associated heap bloc for a specific address
 * \param void* startAddress, address for which we are trying to find the allocation block
 * \param int32_t* OUT_startBlock, will contain the start block after execution
 * \param int32_t* OUT_nblock, will contain the lenght of allocation in block after execution
 * \return int8_t, GENSUCCESS if reservatio succeded GENERROR otherwise
 *
 * Based on a start address, this will return (out params) the start
 * block and allocation length for an address. For this to work, the
 * startAddress that is passed in needs to be within the first
 * block of the allocation.
 * This will return -1 if an an error occurs. 0 otherwise.
 */
static int8_t kfindStartBlockAndLengthForAddress(void* startAddress, int32_t* OUT_startBlock, int32_t* OUT_nblock){

    int32_t expectedFirstBlock = ((uint32_t)startAddress - (uint32_t)kernelHeap) / 64;
    int32_t expectedAllocationLength = 0;
    int8_t returnValue = GENERROR;    // Default to error

    // Now we confirm that the expected first block is a first block
    expectedAllocationLength = *(uint8_t*)(kernelHeapArray + expectedFirstBlock);

    if (expectedAllocationLength != 0 && expectedAllocationLength != 0xFF){
        // We have a real first block
        *OUT_startBlock = expectedFirstBlock;
        *OUT_nblock = expectedAllocationLength;
        returnValue = GENSUCCESS;    // Success
    }

    return returnValue;
}

/**
 * \fn int8_t kfree(void* freeBuffer)
 * \brief Free a block of memory by using first address
 * \param void* freeBuffer, pointer to first addres of memory block
 * \return int8_t, GENSUCCESS if reservatio succeded GENERROR otherwise
 *
 * Free return a block of data to 0 before freeing
 * the bloc. The bloc is usable right after it has been freed
 * returns GENERROR if address being freed is not managed by this heap
 */
int8_t kfree(void* freeBuffer){
    int32_t startBlock = 0;
    int32_t nblock = 0;
    int32_t bufferDwordSize;

    if (!kernelHeapIsUsable){
        panic(KERNEL_HEAP, BAD_HEAP);     // Should not be here!
        // Since we are not sure if the heap
        // is usable, abort...
    }

    // Validate address being free is part of the buffer managed by this heap
    if ((uint8_t*)freeBuffer < kernelHeap || (uint8_t*)freeBuffer >= (kernelHeap + (1024 * 1024))){
        return GENERROR;
    }

    if (kfindStartBlockAndLengthForAddress(freeBuffer, &startBlock, &nblock) == GENERROR){
        panic(KERNEL_HEAP, HEAP_MANAGEMENT_ERROR);
    }

    // If we are here, we have correct data in start and nblock
    // We can now zero out the memory buffer
    bufferDwordSize = (nblock * 64) >> 2;
    for (int i = 0; i < bufferDwordSize; i++){
        *(((uint32_t*)freeBuffer) + i) = 0;
    }

    // Buffer has been zeroed time to return allocated bloc to the
    // available block pool...
    kreleaseHeapBlock(startBlock, nblock);

    return GENSUCCESS;
}

/**
 * \fn static void kreleaseHeapBlock(int32_t startBlock, int32_t nbloc)
 * \brief Release a block reservation and return it to free blocks
 * \param int32_t startBlock, The first block to be released
 * \param int32_t nbloc, length of the release
 * \return void
 *
 * This will modify the kernelHeapArray so that blocks belonging
 * to an allocation are returned to the available block list.
 * After this operation these block are fully usable. Memory
 * targeted by these blocks needs to be zeroed before calling
 * this function.
 */
static void kreleaseHeapBlock(int32_t startBlock, int32_t nbloc){
    // Validates start block boundaries
    if (startBlock < 0 || startBlock >= (4096 * 4)){
        panic(KERNEL_HEAP, HEAP_MANAGEMENT_ERROR);
    }

    // Validate nbloc boundaries
    if (nbloc < 0 || (startBlock + nbloc) >= (4096 * 4)){
        panic(KERNEL_HEAP, HEAP_MANAGEMENT_ERROR);
    }

    // We should be good to go
    for (int i = startBlock; i < (startBlock + nbloc); i++){
        *(kernelHeapArray + i) = 0;
    }
}


/**
 * \fn void kvalidateHeap()
 * \brief Validates the heap before we can use it
 * \return void
 *
 * This validates the early heap before we can use it
 */
void kvalidateHeap(){
    if (!kernelHeapIsUsable){

        // Make sure that we have a 16KB array for heap management
        if ( (kernelHeap - kernelHeapArray) == (4096 * 4) ){
            kernelHeapIsUsable = 1;
        }else{
            panic(KERNEL_HEAP, BAD_HEAP);     // If we are here, something is wrong with memory
                                                    // The kernel is NOT in a runnable state
        }
    }
}

/**
 * \fn void kinitHeap()
 * \brief Initialize the heap so it can be used
 * \return void
 *
 * This initialize the heap array so it can be used
 * The heap is also initialized since it is only returned
 * to 0 when memory is freed.
 */
void kinitHeap(){
    kvalidateHeap();

    // Now scan heap array to set it to 0
    for (uint16_t i = 0; i < (4096 * 4); i++){
        *(kernelHeapArray + i) = 0;
    }

    // Now scan full heap and set it to 0
    for (uint32_t i = 0; i < (1024 * 1024); i += 4){
        *(uint32_t*)(kernelHeap + i) = 0;   // Small optimization so initialisation is faster
    }
}