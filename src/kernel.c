#include <types.h>
#include <drivers/screen.h>
#include <drivers/terminal.h>

#include <bootboot.h>

#define rect(startx, col)					\
for(int x = startx; x < startx+20; x++)		\
{											\
	for(int y = 20; y < 40; y++)			\
	{										\
		putpixel(x, y, col);				\
	}										\
}

void _start()
{
	ScreenInit();
	print_prc("Booting Iyon...");
	while(true);
}
