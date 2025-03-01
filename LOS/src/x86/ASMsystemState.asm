align 4
section .text
global _getStackPointerForStackTrace
_getStackPointerForStackTrace:
    ; This function simply returns esp
    ; it is meant to be used with troubleshooting code
    mov eax, esp
    ret

align 4
global _getSystemState
_getSystemState:
    ; This function returns the system state as per
    ; the systemState struct defined in systemState.h
    ; The state is returned into the pointer that is passed in.
    ; Here is a copy of that struct for reference... Might be out of date...
    ; struct sState {         // Offset within structure
    ;    uint32_t cr0;       // 0
    ;    uint32_t cr1;       // 4
    ;    uint32_t cr2;       // 8
    ;    uint32_t cr3;       // 12
    ;    uint32_t cr4;       // 16
    ;    uint32_t eflags;    // 20
    ;    uint32_t gdtr[2];   // 24
    ;    uint32_t idtr[2];   // 32
    ; };

    push ebp
    mov ebp, esp
    push ebx

    sub esp, 8

    mov eax, [ebp + 8]      ; Get the pointer that has been passed in
    mov ebx, cr0
    mov [eax + 0], ebx
    ;mov ebx, cr1           ; cr1 is defined as "reserved" in Intel documentation...
    ;mov [eax + 4], ebx     ; uncomment only if you want to see QEMU crap out...
    mov ebx, cr2
    mov [eax + 8], ebx
    mov ebx, cr3
    mov [eax + 12], ebx
    mov ebx, cr4
    mov [eax + 16], ebx
    pushfd
    pop ebx
    mov [eax + 20], ebx

    sgdt [esp]              ; Get and parse GDTR data
    mov ebx, [esp + 2]
    mov [eax + 24], ebx
    mov ebx, [esp]
    and ebx, 0xFFFF
    mov [eax + 28], ebx

    sidt [esp]              ; Get and parse IDTR data
    mov ebx, [esp + 2]
    mov [eax + 32], ebx
    mov ebx, [esp]
    and ebx, 0xFFFF
    mov [eax + 36], ebx

    add esp, 8
    pop ebx
    pop ebp
    ret

align 4
global _getMemoryState
_getMemoryState:
    ; This function gets information transited from the BootLoader.
    ; We are mostly interested in memory information. The method used
    ; here is simple and not perfect. A (little bit) more complicated
    ; and more precise/correct way of doing this is documented in
    ; the multiboot specification using memory maps. However, the goal
    ; in the current project is to keep things as simple as possible.
    ; Function prototype is:
    ; void _getMemoryState(uint32_t* low, uint32_t* high);

    push ebp
    mov ebp, esp

    ; As per multiboot spec, the multiboot structure is in EBX after
    ; control transfer. The amount of low memory (In KB) (start at address 0)
    ; will be at offset 4. The amount of high memory* (In KB) (start at 1 MB)
    ; will be at offset 8.
    ; * This is a language abuse and not all memory will be showed in here
    ;   See multiboot specification for more details... We will however
    ;   be using it as so.

    mov ecx, [ebx + 4]      ; Get low mem value from structure
    mov eax, [ebp + 8]      ; Get the low mem return pointer
    mov [eax], ecx          ; Returns the value

    mov ecx, [ebx + 8]      ; Get high mem value from structure
    mov eax, [ebp + 12]     ; Get the high mem return pointer
    mov [eax], ecx          ; Returns the value

    pop ebp
    ret


