Note: This file was translated to English by chatGPT. Please refer to the french version in case you have any issues.

# Building the Cross Compiler

## Prerequisites:
Make sure you have followed the preparation guidelines for the training. Specifically, the following packages should be installed:

- `libgmp-dev`
- `libmpfr-dev`
- `libmpc-dev`
- `libisl-dev`

You should also have downloaded the source code for **GCC 6.2** and **Binutils 2.27**.

## Building the Compiler:

1. Create the directory `~/src`
2. Extract **GCC** to `~/src/gcc`
3. Extract **Binutils** to `~/src/binutils`
4. Create the following directories:
   ```sh
   mkdir ~/i686-elf-CC
   mkdir ~/i686-elf-CC/binutils-i686-elf-obj
   mkdir ~/i686-elf-CC/i686-elf
   ```
5. Navigate to the directory `~/i686-elf-CC/binutils-i686-elf-obj`
6. Run the following commands:
   ```sh
   ~/src/binutils/configure --prefix=/home/user/i686-elf-CC/i686-elf --target=i686-elf --disable-werror
   make
   make install
   ```
7. After executing these commands, the **Binutils** binaries will be located in `~/i686-elf-CC/i686-elf`.  
   It is important to add this directory to your `PATH`. You can use the following command:
   ```sh
   export PATH="/home/user/i686-elf-CC/i686-elf/bin:$PATH"
   ```
8. You can verify that the command worked by running:
   ```sh
   echo $PATH
   ```
9. Create the directory and navigate into it:
   ```sh
   mkdir ~/i686-elf-CC/gcc-i686-elf-obj
   cd ~/i686-elf-CC/gcc-i686-elf-obj
   ```
10. Run the following command:
    ```sh
    ~/src/gcc/configure --prefix=/home/user/i686-elf-CC/i686-elf --target=i686-elf --program-prefix=i686-elf --without-headers --enable-languages=c,c++
    ```
11. Now, execute the following commands:
    ```sh
    make all-gcc
    make all-target-libgcc
    make install-gcc
    make install-target-libgcc
    ```
12. If everything worked correctly, the **cross compiler** should be located in `~/i686-elf-CC/i686-elf/bin`.

---

## Validating the Compiler

To validate that your compiler is working properly, open the **Validation** folder and execute the `buildRun` script.  
If your compiler is functioning correctly, a message should appear in the **qemu** window.  

If you have any doubts, ask for help.
