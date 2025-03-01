#if !defined(__i386__)
    #error "LOS only support i386 target"
#endif

#include "init.h"

enum STANDARD_COLOR{
    BLACK = 0,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    WHITE,
    GRAY,
    BBLUE,
    BGREEN,
    BCYAN,
    BRED,
    BMAGENTA,
    BYELLOW,
    BWHITE
};

/*
 * Screen management declaration
 */
#define SCREEN_BUFFER ((short int*)0xB8000)   // Screen buffer is expected to be at this physical address

/*
 * Screen helper macros
 */

#define buildDisplayChar(character, color)    ((color << 8) | character)
#define buildDisplayColor(fg, bg)             (bg << 4 | fg)

int LOS_init(){
    
    char* grats = "Compiler working!";
    char* iterator = grats;
    short int* display = SCREEN_BUFFER;
    short int color = buildDisplayColor(BBLUE, GRAY);
    short int dispChar = 0;

    do{
        dispChar = buildDisplayChar(*iterator, color);
        *display = dispChar;
        display++;
        iterator++;
    }while(*iterator != 0);
    

    while(1){;}
    return 0;
}


