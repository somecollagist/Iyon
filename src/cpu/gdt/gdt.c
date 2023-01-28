#include "gdt.h"
#include <types.h>
#include <drivers/terminal.h>

#define CreateGDTEntry(base, limit, access, flags)\
{\
	(uint16_t)(((uint32_t)limit) & 0xFFFF),\
	(uint16_t)(((uint64_t)base) & 0xFFFF),\
	(uint8_t)((((uint64_t)base) >> 16) & 0xFF),\
	((uint8_t)access),\
	(uint8_t)(((((uint32_t)limit) >> 12) & 0xF) |\
		(((uint8_t)flags) & 0xF0)),\
	(uint8_t)((((uint64_t)base) >> 24) & 0xFF)\
}

__attribute__((aligned(0x1000)))
GDT DefaultGDT = {
	CreateGDTEntry(0x00, 0x00000, 0x00, 0x00),	// Null
	CreateGDTEntry(0x00, 0xFFFFF, 0x9A, 0xA0),	// Kernel Code
	CreateGDTEntry(0x00, 0xFFFFF, 0x92, 0xC0),	// Kernel Data
	CreateGDTEntry(0x00, 0xFFFFF, 0xFA, 0xA0),	// User Code
	CreateGDTEntry(0x00, 0xFFFFF, 0xF2, 0xC0),	// User Data
};

TSS _tss = {
	0, {}, 0, {}, 0, 0, 0, 0
};

//See: loadgdt.asm
extern void LoadGDT(GDTDescriptor* gdtDescriptor);

void InitGDT()
{
	print_prc("Loading GDT...\n");

	uint64_t tssaddr = &_tss;
	uint32_t sizetss = sizeof(TSS);
	DefaultGDT.TSS.LimitLow = ((uint32_t)sizetss) & 0xFFFF;
	DefaultGDT.TSS.LimitFlags = ((((uint32_t)sizetss) >> 12) & 0xF);
	DefaultGDT.TSS.BaseLow = ((uint64_t)tssaddr) & 0xFFFF;
	DefaultGDT.TSS.BaseMid = (((uint64_t)tssaddr) >> 16) & 0xFF;
	DefaultGDT.TSS.BaseHigh = (((uint64_t)tssaddr) >> 24) & 0xFF;
	DefaultGDT.TSS.BaseTop = (((uint64_t)tssaddr) >> 32) & 0xFFFFFFFF;
	DefaultGDT.TSS.Access = 0x89;
	DefaultGDT.TSS.Reserved = 0;

	GDTDescriptor GDTDesc;
	GDTDesc.Size = sizeof(GDT) - 1;
	GDTDesc.Offset = (uint64_t)&DefaultGDT;
	LoadGDT(&GDTDesc);
	
	print_yay("Loaded GDT!\n");
}