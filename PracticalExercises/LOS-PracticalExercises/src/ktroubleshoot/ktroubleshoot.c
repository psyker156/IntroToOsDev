/**
 * \file ktroubleshoot.c
 * \brief Contains general troubleshooting code
 * \date 02/08/16
 */

#include "../include/ktroubleshoot.h"

char* excp_0 = "  Divide error (vector 0)";
char* excp_1 = "  Debug exception (vector 1)";
char* excp_2 = "  NMI Interrupt (vector 2)";
char* excp_3 = "  Breakpoint (vector 3)";
char* excp_4 = "  Overflow (vector 4)";
char* excp_5 = "  BOUND Range Exceeded (vector 5)";
char* excp_6 = "  Invalid Opcode (vector 6)";
char* excp_7 = "  Device Not Available (vector 7)";
char* excp_8 = "  Double Fault (vector 8)";
char* excp_9 = "  Coprocessor Segment Overrun (vector 9)";
char* excp_10 = "  Invalid TSS (vector 10)";
char* excp_11 = "  Segment Not Present (vector 11)";
char* excp_12 = "  Stack-Segment Fault (vector 12)";
char* excp_13 = "  General Protection (vector 13)";
char* excp_14 = "  Page Fault (vector 14)";
char* excp_16 = "  x87 FPU Floating-Point Error (vector 16)";
char* excp_17 = "  Alignment Check (vector 17)";
char* excp_18 = "  Machine Check (vector 18)";
char* excp_19 = "  SIMD Floating-Point Exception (vector 19)";
char* excp_20 = "  Virtualization Exception (vector 20)";
char* excp_unkwn = "  Unknown exception received";

/**
 * \fn void displayException(uint8_t handlerSource);
 * \brief This simply displays an error message that is appropriate to the exception received
 * \param uint8_t handlerSource
 * \return void
 */
void displayException(uint8_t handlerSource){
    char* excp = "Exception has been received:";
    kprint(excp);

    switch(handlerSource){
        case 0:
            kprint(excp_0);
            break;
        case 1:
            kprint(excp_1);
            break;
        case 2:
            kprint(excp_2);
            break;
        case 3:
            kprint(excp_3);
            break;
        case 4:
            kprint(excp_4);
            break;
        case 5:
            kprint(excp_5);
            break;
        case 6:
            kprint(excp_6);
            break;
        case 7:
            kprint(excp_7);
            break;
        case 8:
            kprint(excp_8);
            break;
        case 9:
            kprint(excp_9);
            break;
        case 10:
            kprint(excp_10);
            break;
        case 11:
            kprint(excp_11);
            break;
        case 12:
            kprint(excp_12);
            break;
        case 13:
            kprint(excp_13);
            break;
        case 14:
            kprint(excp_14);
            break;
        case 16:
            kprint(excp_16);
            break;
        case 17:
            kprint(excp_17);
            break;
        case 18:
            kprint(excp_18);
            break;
        case 19:
            kprint(excp_19);
            break;
        case 20:
            kprint(excp_20);
            break;
        default:
            kprint(excp_unkwn);
            break;
    }
}

/**
 * \fn void panic(uint32_t subsystemCode, uint32_t errorCode)
 * \brief Prints an error code and a stack trace
 * \param uint32_t subsystemCode,
 * \param uint32_t errorCode
 * \return This function never returns and end in an infinite loop
 *
 * This will kill the system. Doing so, it will display the error code
 * and part of the stack trace that lead to this panic call
 */
void panic(uint32_t subsystemCode, uint32_t errorCode){
    // TODO This needs a serious refactor...
    // This code can't rely on any other important function or
    // structure available to the kernel since these could
    // be unavailable. It only relies on "_getStackPointerForStackTrace"
    // and "kitoa"

    uint8_t panicColorCode = buildDisplayColor(RED, BLACK);
    uint16_t displayPosition = 0;
    uint16_t* displayBuffer = (uint16_t*)0xB8000;
    // 0x40 value on following line is volatile and unreliable...
    // It attempts at removing panic stack frame from the stack trace.
    //uint32_t* stackPointer = _getStackPointerForStackTrace() + 0x40;
    uint32_t* stackPointer = _getStackPointerForStackTrace();

    char panicHexErrorCode[9];
    char* panicMessage = "KERNEL PANIC - ERROR CODE:";
    char* stackTopMessage = "STACK TOP AT:";
    char* stackTraceMessage = "STACK TRACE:";

    char* cursor = panicMessage;
    while(*cursor){
        *(displayBuffer + displayPosition) = ((panicColorCode << 8) | *cursor);
        displayPosition++;
        cursor++;
    }

    kitoa(subsystemCode | errorCode, panicHexErrorCode);
    cursor = panicHexErrorCode;
    while(*cursor){
        *(displayBuffer + displayPosition) = ((panicColorCode << 8) | *cursor);
        displayPosition++;
        cursor++;
    }

    for (int i = 0; i < 2; i++){
        *(displayBuffer + displayPosition) = ((panicColorCode << 8) | 0x20);
        displayPosition++;
        cursor++;
    }

    panicColorCode = buildDisplayColor(GREEN, BLACK);

    cursor = stackTopMessage;
    while(*cursor){
        *(displayBuffer + displayPosition) = ((panicColorCode << 8) | *cursor);
        displayPosition++;
        cursor++;
    }

    kitoa((uint32_t)stackPointer, panicHexErrorCode);
    cursor = panicHexErrorCode;
    while(*cursor){
        *(displayBuffer + displayPosition) = ((panicColorCode << 8) | *cursor);
        displayPosition++;
        cursor++;
    }

    for (int i = 0; i < 2; i++){
        *(displayBuffer + displayPosition) = ((panicColorCode << 8) | 0x20);
        displayPosition++;
        cursor++;
    }

    panicColorCode = buildDisplayColor(CYAN, BLACK);
    cursor = stackTraceMessage;
    while(*cursor){
        *(displayBuffer + displayPosition) = ((panicColorCode << 8) | *cursor);
        displayPosition++;
        cursor++;
    }

    for (int i = 0; i < 9; i++){
        *(displayBuffer + displayPosition) = ((panicColorCode << 8) | 0x20);
        displayPosition++;
        cursor++;
    }

    for (int j = 0; j < 4; j++) {
        displayPosition = SEC_LINE_START_POSITION + (20 * j);
        for (int i = 0; i < 24; i++) {
            kitoa((uint32_t)stackPointer, panicHexErrorCode);
            cursor = panicHexErrorCode;
            panicColorCode = BLACK | GREEN;
            while (*cursor) {
                *(displayBuffer + displayPosition) = ((panicColorCode << 8) | *cursor);
                displayPosition++;
                cursor++;
            }

            panicColorCode = buildDisplayColor(RED, BLACK);
            *(displayBuffer + displayPosition) = ((panicColorCode << 8) | ':');
            displayPosition++;

            kitoa(*stackPointer, panicHexErrorCode);
            cursor = panicHexErrorCode;
            panicColorCode = buildDisplayColor(CYAN, BLACK);
            while (*cursor) {
                *(displayBuffer + displayPosition) = ((panicColorCode << 8) | *cursor);
                displayPosition++;
                cursor++;
            }

            for (int i = 0; i < 3; i++) {
                *(displayBuffer + displayPosition) = ((panicColorCode << 8) | 0x20);
                displayPosition++;
                cursor++;
            }
            stackPointer++;
            displayPosition += SPACER;
        }
    }

    // prevent system from running any further
    _stopLOS();
}

/**
 * \fn void nopanic();
 * \brief This function is like panic except that it does not use any parameter
 * \return this does not return! Will loop forever
 *
 * This function is intended to be used to test unstable or unimplemented code.
 */
void nopanic(){
    // TODO This needs a serious refactor...
    // This code can't rely on any other important function or
    // structure available to the kernel since these could
    // be unavailable. It only relies on "_getStackPointerForStackTrace"
    // and "kitoa"
    uint32_t subsystemCode = NO_PANIC_SYSTEM;
    uint32_t errorCode = 0;
    uint8_t panicColorCode = buildDisplayColor(RED, BLACK);
    uint16_t displayPosition = 0;
    uint16_t* displayBuffer = (uint16_t*)0xB8000;
    // 0x40 value on following line is volatile and unreliable...
    // It attempts at removing panic stack frame from the stack trace.
    //uint32_t* stackPointer = _getStackPointerForStackTrace() + 0x40;
    uint32_t* stackPointer = _getStackPointerForStackTrace();

    char panicHexErrorCode[9];
    char* panicMessage = "KERNEL PANIC - ERROR CODE:";
    char* stackTopMessage = "STACK TOP AT:";
    char* stackTraceMessage = "STACK TRACE:";

    char* cursor = panicMessage;
    while(*cursor){
        *(displayBuffer + displayPosition) = ((panicColorCode << 8) | *cursor);
        displayPosition++;
        cursor++;
    }

    kitoa(subsystemCode | errorCode, panicHexErrorCode);
    cursor = panicHexErrorCode;
    while(*cursor){
        *(displayBuffer + displayPosition) = ((panicColorCode << 8) | *cursor);
        displayPosition++;
        cursor++;
    }

    for (int i = 0; i < 2; i++){
        *(displayBuffer + displayPosition) = ((panicColorCode << 8) | 0x20);
        displayPosition++;
        cursor++;
    }

    panicColorCode = buildDisplayColor(GREEN, BLACK);

    cursor = stackTopMessage;
    while(*cursor){
        *(displayBuffer + displayPosition) = ((panicColorCode << 8) | *cursor);
        displayPosition++;
        cursor++;
    }

    kitoa((uint32_t)stackPointer, panicHexErrorCode);
    cursor = panicHexErrorCode;
    while(*cursor){
        *(displayBuffer + displayPosition) = ((panicColorCode << 8) | *cursor);
        displayPosition++;
        cursor++;
    }

    for (int i = 0; i < 2; i++){
        *(displayBuffer + displayPosition) = ((panicColorCode << 8) | 0x20);
        displayPosition++;
        cursor++;
    }

    panicColorCode = buildDisplayColor(CYAN, BLACK);
    cursor = stackTraceMessage;
    while(*cursor){
        *(displayBuffer + displayPosition) = ((panicColorCode << 8) | *cursor);
        displayPosition++;
        cursor++;
    }

    for (int i = 0; i < 9; i++){
        *(displayBuffer + displayPosition) = ((panicColorCode << 8) | 0x20);
        displayPosition++;
        cursor++;
    }

    for (int j = 0; j < 4; j++) {
        displayPosition = SEC_LINE_START_POSITION + (20 * j);
        for (int i = 0; i < 24; i++) {
            kitoa((uint32_t)stackPointer, panicHexErrorCode);
            cursor = panicHexErrorCode;
            panicColorCode = BLACK | GREEN;
            while (*cursor) {
                *(displayBuffer + displayPosition) = ((panicColorCode << 8) | *cursor);
                displayPosition++;
                cursor++;
            }

            panicColorCode = buildDisplayColor(RED, BLACK);
            *(displayBuffer + displayPosition) = ((panicColorCode << 8) | ':');
            displayPosition++;

            kitoa(*stackPointer, panicHexErrorCode);
            cursor = panicHexErrorCode;
            panicColorCode = buildDisplayColor(CYAN, BLACK);
            while (*cursor) {
                *(displayBuffer + displayPosition) = ((panicColorCode << 8) | *cursor);
                displayPosition++;
                cursor++;
            }

            for (int i = 0; i < 3; i++) {
                *(displayBuffer + displayPosition) = ((panicColorCode << 8) | 0x20);
                displayPosition++;
                cursor++;
            }
            stackPointer++;
            displayPosition += SPACER;
        }
    }

    // prevent system from running any further
    _stopLOS();
}


static char* LOSLowMem = "    LowMemory size (KB): ";
static char* LOSHighMem = "    HighMemory size (KB): ";
static char* LOSPaging = "    Paging: ";
static char* LOSCacheDisable = "    CacheDisable: ";
static char* LOSProtected = "    Protected: ";
static char* LOSGDTRBase = "    GDTRBase: ";
static char* LOSGDTRLimit = "    GDTRLimit: ";
static char* LOSIDTRBase = "    IDTRBase: ";
static char* LOSIDTRLimit = "    IDTRLimit: ";

/**
 * \fn void printSystemState()
 * \brief Get system information and display the info to screen
 * \return void
 *
 * This get as much system information as possible and display the info on the screen
 */
void printSystemState(){
    systemState hardwareState;
    uint32_t memLow;
    uint32_t memHigh;
    uint32_t flagValue;
    char line[COL];
    char u32bitHex[9];
    u32bitHex[8] = '\0';

    getSystemState(&hardwareState);
    getMemoryState(&memLow, &memHigh);

    kitoa(memLow, u32bitHex);
    kstrcat(LOSLowMem, u32bitHex, line, COL);
    kprint(line);

    kitoa(memHigh, u32bitHex);
    kstrcat(LOSHighMem, u32bitHex, line, COL);
    kprint(line);

    flagValue = stateCR0Paging(&hardwareState);
    kitoa(flagValue, u32bitHex);
    kstrcat(LOSPaging, u32bitHex, line, COL);
    kprint(line);

    flagValue = stateCR0CacheDisable(&hardwareState);
    kitoa(flagValue, u32bitHex);
    kstrcat(LOSCacheDisable, u32bitHex, line, COL);
    kprint(line);

    flagValue = stateCR0Protection(&hardwareState);
    kitoa(flagValue, u32bitHex);
    kstrcat(LOSProtected, u32bitHex, line, COL);
    kprint(line);

    flagValue = stateGTDRBase(&hardwareState);
    kitoa(flagValue, u32bitHex);
    kstrcat(LOSGDTRBase, u32bitHex, line, COL);
    kprint(line);

    flagValue = stateGTDRLimit(&hardwareState);
    kitoa(flagValue, u32bitHex);
    kstrcat(LOSGDTRLimit, u32bitHex, line, COL);
    kprint(line);

    flagValue = stateIDTRBase(&hardwareState);
    kitoa(flagValue, u32bitHex);
    kstrcat(LOSIDTRBase, u32bitHex, line, COL);
    kprint(line);

    flagValue = stateIDTRLimit(&hardwareState);
    kitoa(flagValue, u32bitHex);
    kstrcat(LOSIDTRLimit, u32bitHex, line, COL);
    kprint(line);
}