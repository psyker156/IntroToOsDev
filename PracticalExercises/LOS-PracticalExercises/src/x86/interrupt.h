/**
 * \file interrupt.c
 * \brief This file contains code related to x86 specific interrupt management/handling
 * \date 29/08/16
 */

#ifndef LOS_INTERRUPT_H
#define LOS_INTERRUPT_H

#include "../include/buffer.h"
#include "../include/types.h"
#include "../include/ktroubleshoot.h"

/*
 * Interrupt constants
 */

#define IDT_BASE 0x2000


/*
 * Interrupt structures
 */

struct _IntGateDesc{
    uint16_t offsetLow;
    uint16_t segSelector;
    uint16_t options;
    uint16_t offsetHigh;
};
typedef struct _IntGateDesc interruptGateDescriptor;

struct _IDTR{
    uint32_t base;
    uint32_t limit;
};


/*
 * Interrupt functions
 */

void ksetupInterrupts();
void kbuildInterruptGate(interruptGateDescriptor* OUT_gate, uint16_t segSelector, uint32_t offset, uint8_t dpl);
extern void _setIDTR(struct _IDTR* buffer);
extern void _activateInterrupts();
extern void _remapPic();


/*
 * Interrupt handlers - Implementation for these is in ASMinterrupt.asm
 */

extern void _handler0();
extern void _handler1();
extern void _handler2();
extern void _handler3();
extern void _handler4();
extern void _handler5();
extern void _handler6();
extern void _handler7();
extern void _handler8();
extern void _handler9();
extern void _handler10();
extern void _handler11();
extern void _handler12();
extern void _handler13();
extern void _handler14();
extern void _handler15();
extern void _handler16();
extern void _handler17();
extern void _handler18();
extern void _handler19();
extern void _handler20();
extern void _handler21();
extern void _handler22();
extern void _handler23();
extern void _handler24();
extern void _handler25();
extern void _handler26();
extern void _handler27();
extern void _handler28();
extern void _handler29();
extern void _handler30();
extern void _handler31();
extern void _handlerClock();
extern void _handlerKeyboard();
extern void _handlerSystemCall();

#endif //LOS_INTERRUPT_H
