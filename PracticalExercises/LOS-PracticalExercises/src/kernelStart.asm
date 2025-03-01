; File: kernelStart.asm
; Creation date: July 31st 2016
; Copyright: 
; License: 



MAGIC    equ  0x1BADB002;               ; Multiboot magic field:
                                        ; https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#Header-magic-fields
MBALIGN  equ  1<<0
MEMINFO  equ  1<<1
FLAGS    equ  MBALIGN | MEMINFO         ; Flags for the multiboot header, please see previous
                                        ; mentioned link for more details

CHECKSUM equ -(MAGIC + FLAGS)           ; The check sum format is defined as a value added to MAGIC
                                        ; and FLAGS that result in the value 0x00000000
                                        ; official info can be found at previously mentioned link
                                        ; what is defined here realy is -(MAGIC + FLAGS) it was summed
                                        ; in python doing a two's complement on MAGIC and FALGS:
                                        ;   t = MAGIC + FLAGS
                                        ;   t ^= 0xFFFFFFFF
                                        ;   t += 1

section .multiboot
align 4
        dd MAGIC
        dd FLAGS
        dd CHECKSUM


section .securityMarker
global _kernelStackEndMarker  ; This will be use to make sure we did not burst the kernel stack

_kernelStackEndMarker:
    dd 0x57AC0E2D
        
section .text
global _start
_start:
    ; One of the first thing we need to do it setup a stack
    ; Without this, no function call!!!
    lea esp, [_stackStart]
    
    ; It is now safe to call into C code
    ; Call into LOS_init so the OS can be properly initialized
    extern LOS_init
    call LOS_init

    hang:
        jmp hang        ; Simply hang the OS
                        ; If we're at this point, the OS is done working
                        ; This should, however, never be reached as the idleProcess
                        ; should kick in. If we are here, something wrong happened.
    
    
section .data 
align 4

global _stackEnd        ; These are global so they can be validated from other part of the code
global _stackStart
_stackEnd:              ; The stack could have been positionned in BSS section and prevent
                        ; the waste of 256 bytes in the file. For simplicity, we leave it
                        ; in data section for now.
    dd 0x57AC0E2D       ; This marker will be validated against _kernelStackEndMarker
                        ; if value has change, a stack overvlow happen at kernel level
                        ; and OS need to die
    times 512 db 0x00   ; Times leaves X data at value. In this case, 256 db initialized to 0
_stackStart:
    dd 0x57AC0E2D

section .bss
align 4096
global _kernelHeapArray
global _kernelHeap
_kernelHeapArray:
    resb (4096 * 4)                 ; Using 16KB
                                    ; This heap will be allocated 64 bytes
                                    ; at a time
_kernelHeap:
    resb (1024 * 1024)              ; This gives 1 MB of _kernelHeap, this is temporary