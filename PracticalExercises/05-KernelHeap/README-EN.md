Note: This file was translated to English by chatGPT. Please refer to the french version in case you have any issues.

# Kernel Heap Implementation

## Exercise Objective
In this exercise, you will implement part of the **kernel heap management system** in **LOS**. Specifically, you will implement the `kmalloc()` function. The first implementation of this function will be **naïve**, and we will revisit it later when discussing **multi-processing**.

---

## Brief Explanation of the Kernel Heap in LOS
The **LOS** kernel heap primarily uses **two memory areas**:

- **`_kernelHeapArray`**: A **bitmap** representing allocations made in `_kernelHeap`.
- **`_kernelHeap`**: The actual memory used for the kernel heap.

The mechanism works as follows:
- `_kernelHeap` is a **1 MB** memory area.
- `_kernelHeapArray` is a **16,384-byte** memory area.
- This allows `_kernelHeapArray` to function as a **bitmap** (byte-wise) with a resolution of **64 bytes per allocation** in `_kernelHeap`.
- In simple terms, `_kernelHeapArray` is an array **tracking allocations** inside `_kernelHeap`.
- These two variables are defined at the **end of the `kernelStart.asm` file**.

### Preliminary Step
Before starting, **read the file** `src/x86/kernelHeap.c`.
- Many **support functions** are already present in the file.
- You are free to **reimplement these functions** if necessary.
- However, the **interface** of the functions `kmalloc`, `kfree`, and `kinitHeap` **must remain unchanged**.
- Due to time constraints, **only the `kmalloc` function** will be implemented in this exercise.

---

## Exercise
The `kmalloc()` function is located in `src/x86/kernelHeap.c`. This is the function you need to implement.

### Responsibilities of the `kmalloc()` Function
Your implementation must meet the **following objectives**:

- **Ensure that the heap is initialized** before usage.
- **Return a pointer of type `void*`**.
- **Calculate the number of blocks** required (with a **64-byte resolution** per allocation).
- **Find and reserve** an available memory block.
- **Compute the memory address** corresponding to the allocation.
- **Return the address of the allocated memory**.

---

## Validating the Heap Functionality
If your implementation is correct, you should be able to **use `kmalloc()` and `kfree()`** after the `kinitHeap()` function is called in `init.c`.

If time allows, it is recommended to **analyze heap behavior using a debugger** while **LOS** is running.

---

## Bonus Question
Why is our implementation considered **naïve**?
What kinds of problems should we expect?
