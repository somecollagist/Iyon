#include "interrupts.h"

#include <types.h>
#include <drivers/terminal.h>

extern void ISRHandler(uint64_t number, uint64_t rsp)
{
	switch(number)
	{
		default:
			kpanic((IntStackFrame*)rsp);
	}
}
