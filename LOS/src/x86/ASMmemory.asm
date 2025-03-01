section .text

align 4
global _loadGDTR
_loadGDTR:
    ; This load the GDTR with the data found at the provided address
    ; and activates the new segments.
    ; Function prototype is:
    ; void _loadGDTR(uint32_t* gdtrBuffer);
    ; Please note that the gdtrBuffer really is a 2 d-word (32 bits) array (total 64 bits)
    ; the first element of the array is the base. Second element is the limit.

    push ebp
    mov ebp, esp
    sub esp, 8          ; For simplicity, build the gdtr buffer on the stack
    mov ecx, [ebp + 8]  ; Get GDTR pointer that was passed on the stack
    mov eax, [ecx]      ; First part of the buffer is the base copy base value to eax
    mov [esp + 2], eax  ; Put base value at esp + 2
    mov eax, [ecx + 4]  ; Second part is limit value get it into eax
    mov [esp], ax       ; Limit is 16 bits, put it at esp

                        ; The buffer on the stack looks like:
                        ; LLLL BBBB BBBB
                        ; Where esp points at the start of buffer, L's represent the 16 bits
                        ; limit field and B's represent the 32 bits base value

    lgdt [esp]          ; Ready to load the GDTR with our 48 bits built buffer

    ; Activate new segments
    jmp 0x08:loadCS     ; CS activation requires a jump... 0x08 is the second descriptor in table
                        ; 0x00 being the first one (also unusable)
loadCS:

    mov eax, 0x10   ; Need to put value in register since not possible to use immediate when
                    ; assigning to a segment register. Value here put in eax is an offset
                    ; within the descriptor table. Data is the second usable descriptor table
                    ; entry.
    mov ds, eax     ; Activates all segment registers
    mov ss, eax
    mov es, eax
    mov fs, eax
    mov gs, eax

    add esp, 8      ; Generic function tear down
    pop ebp
    ret

align 4
global _setCR3
_setCR3:
    ; This function will simply set CR3 register to new value
    ; Function prototype is:
    ; extern void _setCR3(uint32_t cr3Value);
    push ebp
    mov ebp, esp

    mov eax, [ebp + 8]  ; This is the cr3Value passed in
    mov cr3, eax

    pop ebp
    ret


align 4
global _activatePaging
_activatePaging:
    ; This function activates 32 bits paging
    ; The function prototype is:
    ; extern void _activatePaging();
    push ebp
    mov ebp, esp

    mov eax, cr4
    and eax, 0xFFFFFFDF     ; Make sure PAE is deactivated
    mov cr4, eax

    mov eax, cr0
    or eax, 0x80000000      ; Make sure PAGING will be activated
    mov cr0, eax            ; <-- This right here activates paging

    pop ebp
    ret

locker:
    dd 0x00
align 4
global _acquireLock
_acquireLock:
    push ebp
    mov ebp, esp
notAquired:
    xor eax, eax
    mov ecx, 0x01
    lock cmpxchg [locker], ecx
    jne notAquired
acquired:
    pop ebp
    ret

global _releaseLock
_releaseLock:
    push ebp
    mov ebp, esp

    lock mov dword [locker], 0x00

    pop ebp
    ret
