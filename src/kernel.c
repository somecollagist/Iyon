#include <types.h>
#include <cpu/gdt/gdt.h>
#include <cpu/interrupts/interrupts.h>
#include <drivers/screen.h>
#include <drivers/terminal.h>

// Kernel entry point from BOOTBOOT
void _start()
{
	InitScreen();
	InitTerminal();
	print_prc("Booting Iyon...\n");
	InitGDT();
	InitIDT();
	InitIRQ();

	int x = 12/0;
	
	while(true);
}
