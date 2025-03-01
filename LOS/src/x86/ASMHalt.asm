section .text

align 4
global _idleHalt
_idleHalt:
    ; Simple endless halt loop. This is used by the idleProcess to keep the
    ; system usage as low as possible (in a simple way)
    hlt
    jmp _idleHalt

global _stopLOS
_stopLOS:
    ; Clears interrupts and halt the system.
    ; This is meant to be used for debugging purposes.
    cli     ; Disable interrupts
    hlt     ; Halt the system, from here the system is no longer running
