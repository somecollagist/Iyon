#include "interrupts.h"

#include <types.h>
#include <drivers/ports.h>
#include <drivers/terminal.h>

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

typedef void(*IRQHandlerFn)(IntStackFrame* frame);

IRQHandlerFn IRQs[16] = {
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0
};

void InstallIRQHandler(uint32_t irq, void(*handler)(IntStackFrame* frame))
{
	IRQs[irq] = (void*)handler;
}

void UninstallIRQHandler(uint32_t irq)
{
	IRQs[irq] = 0;
}

static volatile bool currentInterrupts[16];

void InitIRQ()
{
	print_prc("Loading IRQ...\n");
	
	SetIDTDescriptor(32,	irq0,	0x8E);
	SetIDTDescriptor(33,	irq1,	0x8E);
	SetIDTDescriptor(34,	irq2,	0x8E);
	SetIDTDescriptor(35,	irq3,	0x8E);
	SetIDTDescriptor(36,	irq4,	0x8E);
	SetIDTDescriptor(37,	irq5,	0x8E);
	SetIDTDescriptor(38,	irq6,	0x8E);
	SetIDTDescriptor(39,	irq7,	0x8E);
	SetIDTDescriptor(40,	irq8,	0x8E);
	SetIDTDescriptor(41,	irq9,	0x8E);
	SetIDTDescriptor(42,	irq10,	0x8E);
	SetIDTDescriptor(43,	irq11,	0x8E);
	SetIDTDescriptor(44,	irq12,	0x8E);
	SetIDTDescriptor(45,	irq13,	0x8E);
	SetIDTDescriptor(46,	irq14,	0x8E);
	SetIDTDescriptor(47,	irq15,	0x8E);

	for(int x = 0; x < 16; x++)
		currentInterrupts[x] = 0;

	asm volatile("sti");

	print_yay("Loaded IRQ!\n");
}

extern void IRQHandler(uint64_t number, uint64_t rsp)
{
	if(IRQs[number-32])
	{
		void (*handler)(IntStackFrame* frame);
		handler = (void(*)(IntStackFrame*))IRQs[number-32];
		handler((IntStackFrame*)rsp);
	}
	PICAcknowledge(number-32);
}
