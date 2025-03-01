align 4
section .text
global _getUsableStackPointer
_getUsableStackPointer:
    ; This function returns an esp
    ; value pointing out of the local stack frame
    mov eax, esp
    sub eax, 0x04   ; Remove local stack frame from the stack!!!
                    ; If you miss this and use that stack as a return
                    ; point, you could(will?) enter an endless loop.
    ret

global _switchStack
_switchStack:
    ; This function switches the stack while allowing
    ; function prototype:
    ; extern void _switchStack(uint32_t newStack, uint32_t* previousProcessStack);
    mov ecx, [esp + 8]  ; Get pointer to old stack storage
    mov eax, [esp + 4]  ; Get the new stack
    test ecx, ecx
    jz noOldStack
    pusha
    mov [ecx], esp      ; Store the old stack so it can be returned to
noOldStack:
    mov esp, eax        ; On return the new process is running!
    popa
    ret