cmake_minimum_required(VERSION 3.5)
project(LOS_PracticalExercises)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/include/buffer.h
    src/include/converter.h
    src/include/kernelHeap.h
    src/include/kerror.h
    src/include/ktroubleshoot.h
    src/include/list.h
    src/include/print.h
    src/include/readKeyboard.h
    src/include/types.h
    src/kinit/init.c
    src/kinit/init.h
    src/kio/clock/clock.c
    src/kio/clock/clock.h
    src/kio/display/display.c
    src/kio/display/display.h
    src/kio/keyboard/charMap.c
    src/kio/keyboard/charMap.h
    src/kio/keyboard/keyboard.c
    src/kio/keyboard/keyboard.h
    src/klib/buffer.c
    src/klib/converter.c
    src/klib/kernelHeap.c
    src/klib/list.c
    src/klib/print.c
    src/klib/readKeyboard.c
    src/kMemoryManagement/memoryManagement.c
    src/kMemoryManagement/memoryManagement.h
    src/kProcessManagement/idleProcess.c
    src/kProcessManagement/idleProcess.h
    src/kProcessManagement/processManagement.c
    src/kProcessManagement/processManagement.h
    src/kProcessManagement/processSynchronisation.h
    src/kProcessManagement/readcProcess.c
    src/kProcessManagement/readcProcess.h
    src/kProcessManagement/readkProcess.c
    src/kProcessManagement/readkProcess.h
    src/kSystemServices/baseService.c
    src/kSystemServices/baseService.h
    src/ktroubleshoot/ktroubleshoot.c
    src/x86/interrupt.c
    src/x86/interrupt.h
    src/x86/memory.c
    src/x86/memory.h
    src/x86/systemState.c
    src/x86/systemState.h
    src/kernelStart.asm
    .gdbinit
    buildRun
    debugRun
    LOSLink.ld
    makefile)

add_executable(LOS_PracticalExercises ${SOURCE_FILES})