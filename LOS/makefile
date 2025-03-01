all: bin/kernel.bin

SOURCE_DIR := src
BUILD_DIR := obj
BIN_DIR := bin
C_SOURCE_FILES := $(shell find src -iname "*.c")
ASM_SOURCE_FILES := $(shell find src -iname "*.asm")
OBJ_FILES := $(addprefix obj/, $(notdir $(C_SOURCE_FILES:.c=.o))) $(addprefix obj/, $(notdir $(ASM_SOURCE_FILES:.asm=.o)))
GCC_C_PARAMS := -c -std=gnu99 -ffreestanding -O0 -Wall -Wextra -g
NASM_PARAMS := -felf32 -g
LINKER_PARAMS := -T LOSLink.ld -ffreestanding -O0 -nostdlib -lgcc -g

# $@ is target name
$(BIN_DIR)/kernel.bin: $(OBJ_FILES)
	i686-elf-gcc-6.1.0 $(LINKER_PARAMS) $^ -o $@

$(BUILD_DIR)/kernelStart.o: src/kernelStart.asm
	nasm $(NASM_PARAMS) $^ -o $@

$(BUILD_DIR)/%.o: src/kinit/%.c
	i686-elf-gcc-6.1.0 $(GCC_C_PARAMS) $^ -o $@

$(BUILD_DIR)/%.o: src/kio/display/%.c
	i686-elf-gcc-6.1.0 $(GCC_C_PARAMS) $^ -o $@

$(BUILD_DIR)/%.o: src/kio/clock/%.c
	i686-elf-gcc-6.1.0 $(GCC_C_PARAMS) $^ -o $@

$(BUILD_DIR)/%.o: src/kio/keyboard/%.c
	i686-elf-gcc-6.1.0 $(GCC_C_PARAMS) $^ -o $@

$(BUILD_DIR)/%.o: src/klib/%.c
	i686-elf-gcc-6.1.0 $(GCC_C_PARAMS) $^ -o $@

$(BUILD_DIR)/%.o: src/kMemoryManagement/%.c
	i686-elf-gcc-6.1.0 $(GCC_C_PARAMS) $^ -o $@

$(BUILD_DIR)/%.o: src/kProcessManagement/%.c
	i686-elf-gcc-6.1.0 $(GCC_C_PARAMS) $^ -o $@

$(BUILD_DIR)/%.o: src/kSystemServices/%.c
	i686-elf-gcc-6.1.0 $(GCC_C_PARAMS) $^ -o $@

$(BUILD_DIR)/%.o: src/ktroubleshoot/%.c
	i686-elf-gcc-6.1.0 $(GCC_C_PARAMS) $^ -o $@

$(BUILD_DIR)/%.o: src/x86/%.asm
	nasm $(NASM_PARAMS) $^ -o $@

$(BUILD_DIR)/%.o: src/x86/%.c
	i686-elf-gcc-6.1.0 $(GCC_C_PARAMS) $^ -o $@

clean:
	rm obj/*
	rm bin/*
	
