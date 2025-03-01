Note: This file was translated to English by chatGPT. Please refer to the french version in case you have any issues.

# Interrupt Management System Implementation

## Exercise Objective
In this exercise, you will implement the necessary code to **enable interrupts** on **x86 32-bit**. Specifically, you will implement the following functions:

- `ksetupInterrupts()` (**partial implementation**)
- `kbuildInterruptGate()`
- `_setIDTR()` (**assembly implementation**)
- `_activateInterrupts()` (**assembly implementation**)

The **first two** functions are located in `src/x86/interrupt.c`, while the **last two** must be implemented in `src/x86/ASMinterrupt.asm`.

---

## Additional Explanation
The functions `_setIDTR` and `_activateInterrupts` must be **implemented in assembly**:

- **The `STI` instruction** enables interrupts.
- **The `LIDT` instruction** loads the **IDTR register**, which is required to handle interrupts.
- **Code examples** were presented in class.
- The configuration of the **IDTR register** is **very similar** to that of the **GDTR register** (refer to the segment configuration exercise if needed).

---

## Exercise Steps
This exercise consists of **four steps**. Since the high-level functions **depend** on `_setIDTR` and `_activateInterrupts`, we will start with the latter.

### 1. Implementing `_activateInterrupts()`
- This function is located in `src/x86/ASMinterrupt.asm`.
- The `STI` instruction can be used to enable interrupts.
  - **Tip**: Research this instruction if needed.
- The implementation should be **simple**, as this function should **only** activate interrupts.
- **Ensure ABI compliance!**

### 2. Implementing `_setIDTR()`
- Research **the `LIDT` instruction** to understand how it works.
- Review the **`_loadGDTR`** function (initial part) for reference.

### 3. Implementing `kbuildInterruptGate()`
- This function builds a **proper interrupt gate descriptor**.
- Refer to **documentation** and **class presentations** for implementation details.

### 4. Completing `ksetupInterrupts()`
- The function is **partially implemented**.
- A section labeled **`Exercise 6 – interrupts`** is marked in the code.
  - **This is where you need to complete the implementation.**

In this function, you must **construct two interrupt descriptors**:

1. **Timer Interrupt**
   - Handled by **`_handlerClock`**.
   - Located at **`IDT_BASE + 32`** in the interrupt vector.

2. **Keyboard Interrupt**
   - Handled by **`_handlerKeyboard`**.
   - Located at **`IDT_BASE + 33`** in the interrupt vector.

ℹ️ **`IDT_BASE`** is defined in `src/x86/interrupt.h` and represents the address where the **interrupt vector** should be configured.

---

## Validating Proper Functionality
To verify that the **interrupt management system** works correctly, you have several options:

- **Access an invalid memory address** (outside the mapped zone). This should trigger a **segmentation fault** displayed by the system.
- **Set breakpoints** using a **debugger** to trace execution.
- **Experimenting with these techniques** is highly recommended to fully understand the system and its functionality.