//Adapted/Stolen from osdev.org

#include "interrupts.h"

#include <drivers/ports.h>

#define PIC1					0x20
#define PIC1_COMMAND			PIC1
#define PIC1_DATA				PIC1+1

#define PIC2					0xA0
#define PIC2_COMMAND			PIC2
#define PIC2_DATA				PIC2+1

#define PIC1_INTERRUPT_START	0x20
#define PIC1_INTERRUPT_END		PIC1_INTERRUPT_START + 7
#define PIC2_INTERRUPT_START	0x28
#define PIC2_INTERRUPT_END		PIC2_INTERRUPT_START + 7

#define ICW1_ICW4				0x01		// ICW4 (not) needed
#define ICW1_SINGLE				0x02		// Single (cascade) mode
#define ICW1_INTERVAL4			0x04		// Call address interval 4 (8)
#define ICW1_LEVEL				0x08		// Level triggered (edge) mode
#define ICW1_INIT				0x10		// Initialization - required!
 
#define ICW4_8086				0x01		// 8086/88 (MCS-80/85) mode
#define ICW4_AUTO				0x02		// Auto (normal) EOI
#define ICW4_BUF_SLAVE			0x08		// Buffered mode/slave
#define ICW4_BUF_MASTER			0x0C		// Buffered mode/master
#define ICW4_SFNM				0x10		// Special fully nested (not)

void PICRemap()
{
	uint8_t a1, a2;
	a1 = inb(PIC1_DATA);
	a2 = inb(PIC2_DATA);

	outb(PIC1_COMMAND, ICW1_INIT|ICW1_ICW4);
	iowait();
	outb(PIC2_COMMAND, ICW1_INIT|ICW1_ICW4);
	iowait();

	outb(PIC1_DATA, 0x20);
	iowait();
	outb(PIC2_DATA, 0x28);
	iowait();

	outb(PIC1_DATA, 4);
	iowait();
	outb(PIC2_DATA, 2);
	iowait();

	outb(PIC1_DATA, ICW4_8086);
	iowait();
	outb(PIC2_DATA, ICW4_8086);

	outb(PIC1_DATA, a1);
	outb(PIC2_DATA, a2);
}

#define PIC_ACKNOWLEDGE			0x20

void PICAcknowledge(uint8_t irq){
	if(irq < 8){
		outb(PIC1_COMMAND, PIC_ACKNOWLEDGE);
	}
	else{
		outb(PIC2_COMMAND, PIC_ACKNOWLEDGE);
	}
}
