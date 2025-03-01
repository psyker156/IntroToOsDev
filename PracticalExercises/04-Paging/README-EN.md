Note: This file was translated to English by chatGPT. Please refer to the french version in case you have any issues.

# Paging Implementation

## Exercise Objective
In this exercise, you will implement **paging** in **LOS**. Specifically, you will build the **tables required by x86** to enable paging. Additionally, you will implement the **assembly code** necessary for enabling paging. All the code to be implemented is located in:

- `src/x86/memory.c`
- `src/x86/ASMmemory.asm`

Make sure you are **familiar with** the `src/x86/memory.h` file before starting. This file contains several elements that will assist you. The key constants for this exercise are:

- `KERNEL_PDT`: Specifies the memory address where the **Page Directory Table (PDT)** should be built.
- `PAGE_SIZE`: Defines the size of a memory page.

---

## Task Description
Before starting, one **crucial** concept must be understood: **Only the first 8 MB of memory should be identity-mapped**. This means that the **first 8 MB of memory should be mapped to a virtual address equal to their physical address**.

A **Page Directory Table (PDT)** requires only **two entries** to map **8 MB** of memory.

### Available Functions
Three functions are provided to assist you:

- `kbuildPDE()`: Builds a **Page Directory** entry.
- `kbuildPTE()`: Builds a **Page Table** entry.
- `kbuildCR3()`: Builds the value to be loaded into the **CR3 register**.
  - This function takes **three parameters**:
    1. The address of the **Page Directory Table**.
    2. **Must be 0** for this exercise.
    3. **Must be 0** for this exercise.

---

## Exercise Steps
The exercise consists of **two steps**:

### 1. Implementing `kinitiatePagingStructuresForBaseOS()`
This function constructs the **data structures** required to enable **32-bit paging**.

1. Build the **data structures** required to map the **first 8 MB** of memory in identity mode.
2. Construct the **CR3 register value** using the `kbuildCR3()` function.
3. Call `_setCR3()` with the newly created **CR3** value.
4. Call `_activatePaging()`.

### 2. Implementing `_setCR3()`
This function has the following prototype:
```c
void _setCR3(uint32_t cr3Value)
```

- **This function must be implemented in assembly.**
- It must **copy the value** of `cr3Value` into the **CR3 register** and return.
- **Warning!** You must follow the **ABI**.

---

## Validating Paging Functionality

To verify that paging works correctly with **identity mapping**, you can:

1. **Write a value** to a memory address between **4 and 8 MB** (in `init.c`, after the code for exercise 4).
2. **Run QEMU** and inspect memory during execution.
3. Use the **`x` and `xp` commands** to inspect **virtual and physical memory**.

### Example usage of the `x` command:
```sh
x /10x <address>
```
The `xp` command works similarly.

If you finish the exercise early, you can examine the **`_activatePaging()` function** to understand how it works.

If needed, refer to **Intel’s Volume 3A manual** for additional documentation.
