#include "terminal.h"

#include <drivers/screen.h>

uint8_t column = 0;
uint8_t row = 0;

const uint8_t TABDEPTH = 4; 

void AssertWriter()
{
	if(column > term_width)
	{
		column = 0;
		row++;
		if(row > term_height)
		{
			row = 0; // TODO: kick over to scroll
		}
	}
}

void print(char *s, Colour foreground)
{
	while(*s)
	{
		switch(*s)
		{
			case '\n':	// Newline (and not using carriage return because I'm not a fucking barbarian)
				column = 0;
				row++;
				break;

			case '\t':	// Tab
				column++;
				while(column% 4 != 0) column++;
				break;

			case '\b':	// Backspace
				// TODO: Write handler
				break;

			default:
				putc(*s, column++, row, foreground, BLACK);
				break;
		}
		s++;
		AssertWriter();
	}
}