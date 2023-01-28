#pragma once

#include <drivers/screen.h>

void InitTerminal();

void print(char* s, Colour foreground, Colour background);

#define TERM_BACKGROUND	BLACK
#define TERM_COL_MSG    VGA_GREY
#define TERM_COL_ERR    COLOUR(0xFF, 0x22, 0x22)
#define TERM_COL_YAY    COLOUR(0x00, 0xAF, 0x32)
#define TERM_COL_ASK    COLOUR(0xD7, 0xFF, 0x5F)
#define TERM_COL_PRC    COLOUR(0x18, 0xB9, 0xEE)

#define print_msg(s) print(s, TERM_COL_MSG, TERM_BACKGROUND)
#define print_err(s) print(s, TERM_COL_ERR, TERM_BACKGROUND)
#define print_yay(s) print(s, TERM_COL_YAY, TERM_BACKGROUND)
#define print_ask(s) print(s, TERM_COL_ASK, TERM_BACKGROUND)
#define print_prc(s) print(s, TERM_COL_PRC, TERM_BACKGROUND)