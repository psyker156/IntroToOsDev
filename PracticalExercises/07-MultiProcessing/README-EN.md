Note: This file was translated to English by chatGPT. Please refer to the french version in case you have any issues.

# Multiprogramming System Implementation

## Exercise Objective
In this exercise, you will implement the **main function** of the **process scheduler**. Since the scheduling system code is relatively long, we will focus only on the **`runScheduler()`** function, located in `src/kProcessManagement/processManagement.c`.

Before starting this exercise, make sure you have a **solid understanding of process scheduling in LOS**. While the function to implement is relatively simple, the **scheduling system itself is complex**.

---

## Before Starting the Exercise
Carefully read the following files:

- `src/kProcessManagement/processManagement.c`
- `src/kProcessManagement/processManagement.h`
- `src/x86/ASMprocessManagement.asm`

Make sure you **understand the key concepts**, as you will need to use several functions from these files to implement `runScheduler()`.

### Note on the `addToReadyQueue` Parameter
- If **`addToReadyQueue == true`**, the **currently running process** must be added to the **ready process list**.

**Reflection:**
1. **Under what conditions should a process be added to this list?**
2. **In what cases will a process not be added to this list?**

---

## Useful Functions
Several functions are available to assist you. You may need the following:

- `addProcessToReadyQueue()` – Adds a process to the **ready process list**.
- `klistRemoveEntryAtIndex()` – Removes an entry from a **process list**.
- `_switchStack()` – Allows the **new process** to take control of the CPU.

You may also need the **macro**:
- `DEFAULT_TIME_SLICE` – Defines the **standard execution time** for a process before control is taken away.

---

## Implementation Details for `runScheduler()`
Your implementation should follow these **steps**:

1. **Add the currently running process** to the **ready process list** if `addToReadyQueue == true`.
2. **Find a process that is ready to execute** from the **waiting process list**.
3. Once the **new process is found**, call the **`_switchStack()`** function to transfer execution to this process.

Although this function appears **simple**, its implementation may be more complex than it seems. **Make sure you fully understand the system before writing your code**.

💡 **Tip:** You will be ready to implement `runScheduler()` when you can **clearly explain how process scheduling works in LOS**.

---

## Validating Functionality
Once the implementation is complete, if all exercises have been successfully completed **and no hidden bugs are present**, the system should:

✅ **Display numbers** on the screen during execution.  
✅ **Show alphabetic keys** on the screen when pressed.

---

## Bonus: A Hidden Bug
There is a **bug in the kernel heap implementation**. This bug may **appear at this stage of the exercise**.

❓ **Even if you don’t encounter it immediately, can you identify the issue and suggest possible solutions to fix it?**
