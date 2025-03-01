align 4
global _readKeyboard
_readKeyboard:
    ; Function reads the keyboard port and return scan code if any was found.
    ; Function prototype is as:
    ; uint8_t _readKeyboard()
    ;
    ; This is however not called from C code.
    in al, 0x60
    ret