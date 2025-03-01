/**
 * \file display.h
 * \brief This contains display related code
 * \date 02/08/16
 */

#include "../../include/ktroubleshoot.h"
#include "../../include/types.h"


#ifndef LOS_DISPLAY_H
#define LOS_DISPLAY_H

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
#define COL 80                  // This OS supports 80x25 for now
#define ROW 25
#define SCREEN_BUFFER 0xB8000   // Screen buffer is expected to be at this physical address
#define WHITESPACE 0x20         // Whitespace ASCII code

/*
 * Screen helper macros
 */

#define buildDisplayChar(character, color)    ((color << 8) | character)
#define buildDisplayColor(fg, bg)             (bg << 4 | fg)

/*
 * Function declaration follows
 */

void disp_clear();
void disp_printLine(uint32_t* line);
void disp_scrollUp();


#endif //LOS_DISPLAY_H
