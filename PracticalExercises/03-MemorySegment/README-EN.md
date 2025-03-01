Note: This file was translated to English by chatGPT. Please refer to the french version in case you have any issues.

# Segmentation Implementation

## Exercise Objectives
In this exercise, you need to implement **segmentation** within **LOS**. Specifically, you must implement the `setupGDT()` function located in `src/x86/memory.c`. This function must use the `loadGDTR(uint32_t* gdtrBuffer)` function, which in turn calls `_loadGDTR(uint32_t* gdtrBuffer)`, to **load the GDTR register** and activate the new segments.

After implementing `setupGDT()`, you can analyze the `_loadGDTR` function code to understand the assembly code that will load the GDTR register and activate the new segments.

Before starting the exercise, it is highly recommended to **familiarize yourself with** the `src/x86/memory.h` file, which contains declarations that can assist you.

## Details of the `setupGDT()` Function
The `setupGDT()` function must prepare all necessary configurations to **load the GDTR register** and the new segments. This function primarily needs to:

1. **Create a NULL segment** (all fields set to 0) as the first entry in the GDT table.
2. **Create a privileged CODE segment** as the second entry in the GDT table:
   - This segment must cover **the entire memory**.
3. **Create a privileged DATA segment** as the third entry in the GDT table:
   - This segment must cover **the entire memory**.
4. **Copy these segments into memory** at the correct location (refer to `GDT_BASE` and look for the `kmemcpy()` function, which will help copy the data).
5. **Prepare the data** to call the `loadGDTR(uint32_t* gdtrBuffer)` function (refer to the `_DTR` structure).
6. **Call the `loadGDTR(uint32_t* gdtrBuffer)` function**.

At every stage, you are free **to modify or adapt the available code** if needed.

You can find guidance on configuring the various segments in the **Intel Programming Manual** (Volume 3A, Chapter 3) or by asking an instructor. However, it is recommended to check the Intel documentation first, as becoming familiar with official documentation is beneficial.

## Validating Segmentation Functionality
After completing these tasks, if your code is working correctly, you can **remove the comment** associated with Exercise 3 in the `src/kinit/init.c` file and **build the system** using the `buildRun` script.

The system state after segmentation setup should be displayed. If everything is functioning correctly, **no visible changes should occur**. However, if an error has been made, the display will likely become **chaotic**, quickly indicating that something is wrong.
