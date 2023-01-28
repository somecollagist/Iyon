#pragma once

#include <types.h>

typedef struct
{
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;
} Colour;

#define COLOUR(r,g,b) (Colour){r,g,b}

#define BLACK		COLOUR(0x00, 0x00, 0x00)
#define WHITE		COLOUR(0xFF, 0xFF, 0xFF)
#define RED			COLOUR(0xFF, 0x00, 0x00)
#define GREEN		COLOUR(0x00, 0xFF, 0x00)
#define BLUE		COLOUR(0x00, 0x00, 0xFF)

// VGA colours
#define VGA_BLUE	COLOUR(0x00, 0x00, 0xAA)
#define VGA_GREEN	COLOUR(0x00, 0xAA, 0x00)
#define VGA_CYAN	COLOUR(0x00, 0xAA, 0xAA)
#define VGA_RED		COLOUR(0xAA, 0x00, 0x00)
#define VGA_PURPLE	COLOUR(0xAA, 0x00, 0xAA)
#define VGA_BROWN	COLOUR(0xAA, 0x55, 0x00)
#define VGA_GREY	COLOUR(0xAA, 0xAA, 0xAA)
#define VGA_DGREY	COLOUR(0x55, 0x55, 0x55)
#define VGA_LBLUE	COLOUR(0x55, 0x55, 0xFF)
#define VGA_LGREEN	COLOUR(0x55, 0xFF, 0xFF)
#define VGA_LCYAN	COLOUR(0x55, 0xFF, 0xFF)
#define VGA_LRED	COLOUR(0xFF, 0x55, 0x55)
#define VGA_LPURPLE	COLOUR(0xFF, 0x55, 0xFF)
#define VGA_YELLOW	COLOUR(0xFF, 0xFF, 0x55)

typedef struct 
{
	Colour foreground;
	Colour background;
} ColourPair;

#define COLOURPAIR(foreground, background) (ColourPair){foreground, background}

/**
 * @brief Initialises the screen
 */
void InitScreen();

// Defined here because that's where the logic is
/**
 * @brief The number of characters the terminal can support vertically
 */
extern uint8_t term_height;
/**
 * @brief The number of characters the terminal can support horizontally
 */
extern uint8_t term_width;

/**
 * @brief Writes a character to a location on the screen
 * @param c Character to write
 * @param x X coordinate of character
 * @param y Y coordinate of character
 * @param foreground Colour of character to write
 * @param background Background to be applied
 */
void putc(char c, int x, int y, Colour foreground, Colour background);