ENTRY(_start)   /* Start is located inside kernelStart file */

SECTIONS
{
    . = 2M;    /* This will get our kernel pass the 2MB zone */
    .text BLOCK(4K) : ALIGN(4K) {
                            obj/kernelStart.o(.multiboot)      /*
                                                                * As per : https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#OS-image-format
                                                                * Multiboot header must be in the first 8192 bytes
                                                                * of the image. Let's prevent some pain later and put it first...
                                                                */
                            *(.text)
                       }
    .securityMarker BLOCK(4K) : ALIGN(4K) { *.(securityMarker)}

    /* Data and bss section for all files goes here */
    .data BLOCK(4K) : ALIGN(4K) { *(.data) }
    .bss BLOCK(4K) : ALIGN(4K) { *(.bss) }
}
