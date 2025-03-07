/**
 * The code present in this file is not part of LOS
 * it is intended to be used to simulate the presence
 * of a kernel mode process. The function being the
 * entry point of the process.
 *
 * In this case, the "process" will read and display
 * any character that is typed in.
 *
 * \date 09/09/16
 */

#include "readkProcess.h"

/*
 * Dummy process entry point to test process wait queues
 */
void readAndDisplayKeyboardKey(){
    char characterString[2] = {0,0};
    while (1){
        characterString[0] = kgetc();
        kprint(characterString);
    }
}