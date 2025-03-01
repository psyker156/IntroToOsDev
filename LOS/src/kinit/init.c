#if !defined(__i386__)
    #error "LOS only support i386 target"
#endif

#include "init.h"

int LOS_init(){
    disp_clear();

    kprint("LOS V0.01 - Init");

    kprint("LOS - System state after BootLoader");
    printSystemState();

    setupGDT();         // Configure and setup memory segments
    kprint("LOS - System state after Segmentation");
    printSystemState();

    kinitiatePagingStructuresForBaseOS();
    kprint("LOS - System state after Paging");
    printSystemState();

    kinitHeap();        // Make the kernel heap usable
    kinitCharMap();     // Initialize the system char map, from here keyboard scan code can be translated

    initializeProcessArray();
    initializeLOSBaseProcesses();

    //ksetupInterrupts(); // Configure and activate interrupts
    //kprint("LOS - System state after Interrupt");
    //printSystemState();

    _switchStack(runningProcess->stack, 0);     // From here, LOS is on its own!
                                                // LOS [processes are now running

    // LOS should never reach this point.

    //panic(0x00, 0x00);
    while(1){;}
    return 0;
}


