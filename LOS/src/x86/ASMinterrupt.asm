section .text

align 4
global _activateInterrupts
_activateInterrupts:
    ; This function will activate the interrupts
    ; This should only be called when the system is fully ready
    ; otherwise code control would get out of hands...
    ; Function prototype:
    ; extern void _activateInterrupts();

    push ebp
    mov ebp, esp

    sti
    pop ebp
    ret

global _remapPic
_remapPic:
    ; This function remaps the PIC so that
    ; it does not overlaps x86 reserved vectors
    ; Function prototype:
    ; extern void _remapPic();

    push ebp
    mov ebp, esp

    MasterC    equ  020h         ; Master command port
    MasterD    equ  021h         ; Master data port
    SlaveC     equ  0A0h         ; Slave command port
    SlaveD     equ  0A1h         ; Slave data port

    mov al, 0x19        ; Put pic in command mode
                        ; bit 4 indicates that this is ICW1
                        ; bit 3 put the PIC in level triggered mode
                        ; bit 2 indicates that the interrupt vectors are 8 bytes apart
                        ; bit 1 indicates that the PIC is in cascade mode
                        ; bit 0 indicates that ICW4 will be issued
    out MasterC, al     ; ICW1
    mov al, 0x20        ; Base for master (Interrupt vector table)
    out MasterD, al     ; ICW2
    mov al, 0x04        ; Connection to slave
    out MasterD, al     ; ICW3
    mov al, 0x01        ; 8086 mode
    out MasterD, al     ; ICW4

    mov al, 0x19        ; Put pic in command mode
    out SlaveC, al      ; ICW1
    mov al, 0x70        ; Base for slave
    out SlaveD, al      ; ICW2
    mov al, 0x02        ; Connection to master
    out SlaveD, al      ; ICW3
    mov al, 0x01        ; 8086 mode
    out SlaveD, al      ; ICW4

    mov al, 0x00        ; Activate all interrupt on master
    out MasterD, al
    mov al, 0x00        ; Activate all interrupt on slave
    out SlaveD, al

    pop ebp
    ret

global _setIDTR
_setIDTR:
    ; This function will set the IDT with the provided values
    ; Function prototype:
    ; extern void _setIDTR(struct _IDTR* buffer);


    push ebp
    mov ebp, esp
    sub esp, 8          ; For simplicity, build the idtr buffer on the stack
    mov ecx, [ebp + 8]  ; Get IDTR pointer that was passed on the stack
    mov eax, [ecx]      ; First part of the buffer is the base copy base value to eax
    mov [esp + 2], eax  ; Put base value at esp + 2
    mov eax, [ecx + 4]  ; Second part is limit value get it into eax
    mov [esp], ax       ; Limit is 16 bits, put it at esp

                        ; The buffer on the stack looks like:
                        ; LLLL BBBB BBBB
                        ; Where esp points at the start of buffer, L's represent the 16 bits
                        ; limit field and B's represent the 32 bits base value

    lidt [esp]          ; Ready to load the IDTR with our 48 bits built buffer

    add esp, 8
    pop ebp
    ret

global _ackIntRet
_ackIntRet:

; Make all handler global so we can use them outside of assembly code.
global _handler0
global _handler1
global _handler2
global _handler3
global _handler4
global _handler5
global _handler6
global _handler7
global _handler8
global _handler9
global _handler10
global _handler11
global _handler12
global _handler13
global _handler14
global _handler15
global _handler16
global _handler17
global _handler18
global _handler19
global _handler20
global _handler21
global _handler22
global _handler23
global _handler24
global _handler25
global _handler26
global _handler27
global _handler28
global _handler29
global _handler30
global _handler31
global _handlerClock
global _handlerKeyboard
global _handlerSystemCall

align 4
extern panic
extern displayException
_handler0:
    push 0
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler1:
    push 1
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler2:
    push 2
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler3:
    push 3
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler4:
    push 4
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler5:
    push 5
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler6:
    push 6
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler7:
    push 7
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler8:
    push 8
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler9:
    push 9
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler10:
    push 10
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler11:
    push 11
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler12:
    push 12
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler13:
    push 13
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler14:
    push 14
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler15:
    push 15
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler16:
    push 16
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler17:
    push 17
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler18:
    push 18
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler19:
    push 19
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler20:
    push 20
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler21:
    push 21
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler22:
    push 22
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler23:
    push 23
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler24:
    push 24
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler25:
    push 25
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler26:
    push 26
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler27:
    push 27
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler28:
    push 28
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler29:
    push 29
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler30:
    push 30
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.
_handler31:
    push 31
    call displayException
    add esp, 4
    hlt                     ; Not handling it for now, halting.


_handlerClock:              ; This is technically handler #32
extern khandleTick
global _schedulerReturn
    pusha
    mov al, 0x20            ; Interrupt ACK
    out 0x20, al; ack irq
    out 0xA0, al; ack irq

    call khandleTick
_schedulerReturn:
    popa
    iret

_handlerKeyboard:           ; This is technically handler #33
extern _readKeyboard
extern khandleKeyboard
    pusha
    mov al, 0x20            ; Interrupt ACK
    out 0x20, al; ack irq
    out 0xA0, al; ack irq

    xor eax, eax
    call _readKeyboard
    test eax, eax
    je handlerK_NoData

    push eax
    call khandleKeyboard
    add esp, 0x04
handlerK_NoData:
    popa
    iret

_handlerSystemCall:         ; This will be mapped to 0x80 similar to LINUX so it's easy to remember
                            ; This is software, no need to acknowledge the interrupt
    pusha

    popa
    iret