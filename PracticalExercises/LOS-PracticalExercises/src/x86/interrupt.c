/**
 * \file interrupt.c
 * \brief This file contains code related to x86 specific interrupt management/handling
 * \date 29/08/16
 */

#include "interrupt.h"

/**
 * \fn void ksetupInterrupts();
 * \brief Makes the interrupts usable on the system
 * \return void
 *
 * This function deals with all interrupts related things. It sets up the IDT, remaps the PIC
 * and activate interrupts on the system.
 */
void ksetupInterrupts(){
    interruptGateDescriptor stepDescriptor;
    struct _IDTR idtr;

    // First 32 handlers are for Intel defined exceptions
    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler0, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 0 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler1, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 1 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler2, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 2 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler3, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 3 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler4, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 4 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler5, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 5 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler6, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 6 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler7, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 7 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler8, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 8 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler9, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 9 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler10, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 10 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler11, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 11 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler12, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 12 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler13, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 13 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler14, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 14 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler15, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 15 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler16, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 16 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler17, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 17 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler18, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 18 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler19, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 19 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler20, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 20 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler21, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 21 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler22, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 22 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler23, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 23 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler24, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 24 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler25, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 25 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler26, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 26 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler27, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 27 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler28, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 28 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler29, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 29 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler30, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 30 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&_handler31, 0x00);
    kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + 31 * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));

    // Put generic handler in case one of these is called...
    for (int i=32; i<=255; i++){
        kbuildInterruptGate(&stepDescriptor, 0x08, (uint32_t)&nopanic, 0x00);
        kmemcpy((uint8_t*)&stepDescriptor, (uint8_t*)(IDT_BASE + i * sizeof(interruptGateDescriptor)), sizeof(interruptGateDescriptor));
    }

    // LOS will only handle keyboard, clock and system call type interrupts

    // Exercise 6 - interrupts code goes here

    idtr.base = IDT_BASE;
    idtr.limit = 0x800;

    _setIDTR(&idtr);        // Puts IDT in memory
    _remapPic();            // Makes sure intel exception does not overlaps PIC interrupts
    _activateInterrupts();  // Activates the interrupts!
}
/**
 * \fn void kbuildInterruptGate(interruptGateDescriptor* OUT_gate, uint16_t segSelector, uint32_t offset, uint8_t dpl);
 * \brief Helper function that builds interrupts gates for the user.
 * \param interruptGateDescriptor* OUT_gate, The gate descriptor (OUTPUT)
 * \param uint16_t segSelector, Segment selector for this gate
 * \param uint32_t offset, Handler offset
 * \param uint8_t dpl, Handler privilege level
 * \return void
 *
 */
void kbuildInterruptGate(interruptGateDescriptor* OUT_gate, uint16_t segSelector, uint32_t offset, uint8_t dpl){
    // Implement function here
}

