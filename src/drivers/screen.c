/* drivers/screen.c
	The bootloader is super nice and loads up the framebuffer for us right from the get-go.
*/

#include "screen.h"

#include <types.h>
#include <bootboot.h>

extern BOOTBOOT bootboot;					// See bootboot.h
extern unsigned char environment[4096];		// Configuration for UTF-8 key-value pairs
extern uint8_t fb;							// Linear mapped framebuffer

int column;
int row;

int scanline;
int width;
int height;
int bpl;

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

psf2_t* font;

void ScreenInit()
{
	scanline	= bootboot.fb_scanline;
	width		= bootboot.fb_width;
	height		= bootboot.fb_height;

	font		= (psf2_t*)&_binary___src_font_psf_start;
	bpl			= (font->width+7)/8;
}