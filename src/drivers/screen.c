/* drivers/screen.c
	The bootloader is super nice and loads up the framebuffer for us right from the get-go.
*/

#include "screen.h"

#include <types.h>

#include <bootboot.h>

extern BOOTBOOT bootboot;					// See bootboot.h
extern unsigned char environment[4096];		// Configuration for UTF-8 key-value pairs
extern uint8_t fb;							// Linear mapped framebuffer

typedef struct {
	uint32_t magic;
	uint32_t version;
	uint32_t headersize;
	uint32_t flags;
	uint32_t numglyph;
	uint32_t bytesperglyph;
	uint32_t height;
	uint32_t width;
	uint8_t glyphs;
} __attribute__((packed)) psf2_t;
extern volatile unsigned char _binary___src_font_psf_start;

psf2_t* font;								// Instance of currently laoded font (see src/font.psf)
int bytesperline;							// Number of bytes per line of a glyph

int term_height;
int term_width;

void ScreenInit()
{
	font			= (psf2_t*)&_binary___src_font_psf_start;
	bytesperline	= (font->width+7)/8;

	term_height		= bootboot.fb_height / font->height;
	term_width		= bootboot.fb_width / font->width;
}

void putpixel(int x, int y, Colour col)
{
	unsigned offset = ((y)*bootboot.fb_scanline)+4*x;							// Calculate framebuffer byte offset
	uint32_t* pixel = (uint32_t*)(&fb + offset);								// Reference to pixel (include framebuffer)
	*pixel = (col.Red << 16) | (col.Green << 8) | (col.Blue);					// Write colour data
}

void putc(char c, int x, int y, Colour foregorund, Colour background)
{
	unsigned char *glyphline = (unsigned char*)&_binary___src_font_psf_start	// Font location
							+ font->headersize									// Skip past the header
							+ (c > 0 && c < font->numglyph ? c : 0)				// Find the offset within the font
							* font->bytesperglyph;								// Multiply by offset scalar

	int mask;																	// Binary mask to filter for pixel of font, init to zero
	for(int _y = 0; _y < font->height; _y++)
	{
		mask = 1 << (font->width-1);											// Access the first bit
		for(int _x = 0; _x < font->width; _x++)
		{
			if(((int)*glyphline)&mask)
				putpixel((x*font->width)+_x, (y*font->height)+_y, foregorund);	// Draw a pixel if the font ordains it to exist by the mask
			else
				putpixel((x*font->width)+_x, (y*font->height)+_y, background);	// Otherwise make it blank

			mask>>=1;															// Cycle the mask
		}
		glyphline += bytesperline;												// Go to next line of glyph
	}
}