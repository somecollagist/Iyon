#include <types.h>
#include <cpu/gdt/gdt.h>
#include <cpu/interrupts/interrupts.h>
#include <drivers/screen.h>
#include <drivers/terminal.h>

// Kernel entry point from BOOTBOOT
void _start()
{
	init();

	int x = 12/0;
	
	while(true);
}

// Super hacky solution to get around multicore BOOTBOOT
bool initflipped = false;
void init()
{
	if(initflipped) return;
	initflipped = true;	// Lock other cores from running this
	InitScreen();
	InitTerminal();
	print_prc("Booting Iyon...\n");
	InitGDT();
	InitIDT();
	InitIRQ();
}
