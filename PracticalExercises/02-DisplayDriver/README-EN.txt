Note: This file was translated to English by chatGPT. Please refer to the french version in case you have any issues.

# Display Driver Implementation

## General Explanation of the Labs
Before starting, make a copy of the `LOS-PracticalExercises` directory since all practical exercises will use this same base. The exercises are incremental, so this base will be used throughout the training. All exercises will start from the `src/kinit/init.c` file.

You should familiarize yourself with this file immediately. 
Each exercise has a starting point inside the `LOS_init` function in this file. Please remove the exercise comments at the beginning of each exercise. For example, the comment on line 9 of `src/kinit/init.c` must be removed before starting the lab. If you have any doubts or questions, feel free to ask for help.

## Lab Explanation
In this lab, you will complete the implementation of the display driver used by **LOS**. To do this, you will use the source code in the `LOS-PracticalExercises` directory. The display driver is located in `src/kio/display`.  
This exercise consists of **two steps**:

### Step 1
The macros to be implemented are located in the `src/kio/display/display.h` file at lines 46 and 47.

- The `buildDisplayColor(fg, bg)` macro must use the `STANDARD_COLOR` enumeration to construct an **8-bit** number in the format `0bBBBB FFFF`, where `B` represents the background color and `F` represents the foreground (text) color.
- The `buildDisplayChar(character, color)` macro must construct a **16-bit** number representing a character that can be displayed on the screen. The character should be formatted as `0xCCRR`, where `C` represents the display color and `R` represents the ASCII character to be displayed.

### Step 2
Make sure you read the `display.h` file before starting this part of the exercise. Several elements are provided to help you. This part heavily depends on **display memory**, which is located at the address defined by the `SCREEN_BUFFER` macro. This memory is organized as an **80-column by 25-row** buffer.

1. **Implement `disp_clear()`**
   - This function takes no parameters.
   - It must clear the entire display, making it appear as a black screen.

2. **Implement `disp_printLine(uint32_t* line)`**
   - This function prints a line at the bottom row of the screen.
   - It calls `disp_scrollUp()` to scroll the display.
   - **Important Note**: The `line` parameter is a pointer to a memory area that is already formatted for display. You **do not** need to use the `buildDisplayColor` and `buildDisplayChar` macros on this data.
   - You can review the functions that call `disp_printLine()` to better understand the function's usage context.

3. **Implement `disp_scrollUp()`**
   - This function takes no parameters.
   - It scrolls the text on the screen upwards, inserting a blank line at the bottom.

Once the exercise is completed, **LOS** will be able to execute lines **10 to 15** of the `init.c` file. You can verify that your code is working correctly by running the `buildRun` script.
