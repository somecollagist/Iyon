#include <types.h>
#include <cpu/gdt/gdt.h>
#include <cpu/interrupts/interrupts.h>
#include <drivers/screen.h>
#include <drivers/terminal.h>

#include <bootboot.h>

extern BOOTBOOT bootboot;					// See bootboot.h

void init()
{
	InitScreen();
	InitTerminal();
	print_prc("Booting Iyon...\n");
	InitGDT();
	InitIDT();
	InitIRQ();
	while(true){}
}

void main()
{
	while(true){}
}
