#include "interrupts.h"

#include <types.h>
#include <drivers/terminal.h>

#define IDTENTRIES 256

__attribute__((aligned(0x10)))
static IDTEntry IDT[IDTENTRIES];
static IDTR IDTR_T;

// Populates the given IDT descriptor
void SetIDTDescriptor(uint8_t idx, void* isr, uint8_t attrs)
{
	IDTEntry* entry = &IDT[idx];

	entry->OffsetLow		= (uint16_t)((uint64_t)isr & 0x000000000000FFFF);
	entry->SegmentSelector	= 0x08;
	entry->IST				= 0;
	entry->Attributes		= attrs;
	entry->OffsetMid		= (uint16_t)(((uint64_t)isr & 0x00000000FFFF0000) >> 16);
	entry->OffsetHigh		= (uint32_t)(((uint64_t)isr & 0xFFFFFFFF00000000) >> 32);
	entry->Reserved			= 0;
}

// See interrupts.asm
// This points to the ISR structure and populates accordingly
extern void* ISRTable[];

void InitIDT()
{
	print_prc("Loading IDT...\n");
	PICRemap();
	asm volatile("cli");
	IDTR_T.Base		= (uint64_t)&IDT;
	IDTR_T.Limit	= (uint16_t)sizeof(IDTEntry) * IDTENTRIES - 1;

	for(uint8_t idx = 0; idx < 48; idx++)
	{
		SetIDTDescriptor(idx, ISRTable[idx], 0x8E);
	}

	asm volatile("lidtq %0" : : "m"(IDTR_T));	// Load IDT
	print_yay("Loaded IDT!\n");
}