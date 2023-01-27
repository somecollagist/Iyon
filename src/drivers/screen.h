#pragma once

#include <types.h>

typedef struct
{
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;
} Colour;

void ScreenInit();

void putc(char c);
void puts(char* s);

#define COLOUR(r,g,b) (Colour){r,g,b}
#define BLACK	COLOUR(0x00, 0x00, 0x00)
#define WHITE	COLOUR(0xFF, 0xFF, 0xFF)
#define RED		COLOUR(0xFF, 0x00, 0x00)
#define GREEN	COLOUR(0x00, 0xFF, 0x00)
#define BLUE	COLOUR(0x00, 0x00, 0xFF)