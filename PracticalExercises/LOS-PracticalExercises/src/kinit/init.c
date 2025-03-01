#if !defined(__i386__)
    #error "LOS only support i386 target"
#endif

#include "init.h"

int LOS_init(){

    /* Exercise 2 - The display driver
    disp_clear();

    kprint("LOS V0.01 - Init");

    kprint("LOS - System state after BootLoader");
    printSystemState();
    */

    /* Exercise 3 - Setting up segmentation
    setupGDT();         // Configure and setup memory segments
    kprint("LOS - System state after Segmentation");
    printSystemState();
    */

    /* Exercise 4 - Setting up paging
    kinitiatePagingStructuresForBaseOS();
    kprint("LOS - System state after Paging");
    printSystemState();
    */

    /* Exercise 5 - Setting up the heap
    kinitHeap();        // Make the kernel heap usable
    kinitCharMap();     // Initialize the system char map, from here keyboard scan code can be translated
    */


    /* Exercise 6 - Setting up interrupts
    // There would be a race condition here. Can you explain why?
    // ksetupInterrupts(); // Configure and activate interrupts
    // kprint("LOS - System state after Interrupt");
    // printSystemState();
    */

    /* Exercise 7 - Multi processing
    initializeProcessArray();
    initializeLOSBaseProcesses();
    _switchStack(runningProcess->stack, 0);     // From here, LOS is on its own!
                                                // LOS [processes are now running
    */
    // LOS should never reach this point.

    //panic(0x00, 0x00);
    while(1){;}
    return 0;
}


