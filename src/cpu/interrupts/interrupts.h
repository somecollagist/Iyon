#pragma once

#include <types.h>

typedef struct {
	uint16_t	OffsetLow;
	uint16_t	SegmentSelector;
	uint8_t		IST;
	uint8_t		Attributes;
	uint16_t	OffsetMid;
	uint32_t	OffsetHigh;
	uint32_t	Reserved;
} __attribute__((packed)) IDTEntry;

typedef struct {
	uint16_t	Limit;
	uint64_t	Base;
} __attribute__((packed)) IDTR;

typedef struct {
	uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
	uint64_t rbp, rdi, rsi, rdx, rcx, rbx, rax;
	uint64_t int_num, err_code;
	uint64_t rip, cs, rflags, rsp, ss;
} __attribute__((packed)) IntStackFrame;

typedef struct {
	IntStackFrame* rbp;
	uint64_t rip;		// Address where interrupt is called
} __attribute__((packed)) StackFrame;

static const char *IntMsgs[] = {
	// From the Intel Dev Manual:		Type		Error Code	Source
	"Zero Division",				//	Fault		No			DIV and IDIV Instructions
	"Debug",						//	Fault/Trap	No			Breakpoints
	"Non-Maskable Interrupt",		//	Interrupt	No			Non-maskable external interrupt
	"Breakpoint",					//	Trap		No			INT3 Instruction
	"Overflow",						//	Trap		No			INT0 Instruction
	"Bound Range Exceeded",			//	Fault		No			BOUND Instruction
	"Invalid Opcode",				//	Fault		No			Unknown or reserved opcode
	"Device Unavailable",			//	Fault		No			Floating point or WAIT/FWAIT Instruction
	"Double Fault",					//	Abort		Yes (0)		Something that generates an exception
	"Coprocessor Segment Overrun",	//	Fault		No			Floating point (This is legacy and not generated by processors after the 386)
	"Invalid TSS",					//	Fault		Yes			Task switch or TSS access
	"Segment Not Present",			//	Fault		Yes			Loading seg regs or accessing sys segs
	"Stack Fault",					//	Fault		Yes			Stack operations and SS loads
	"General Protection Fault",		//	Fault		Yes			Any memory reference and other protection checks
	"Page Fault",					//	Fault		Yes			Any memory reference
	"System Reserved 1",			//				No
	"x87 FPU Error",				//	Fault		No			x87 FPU Floating point or WAIT/FWAIT Instruction
	"Alignment Check",				//	Fault		Yes (0)		Any data reference in memory
	"Machine Check",				//	Abort		No			From the machine (any codes are source & model dependent)
	"SIMD Floating Point Error",	//	Fault		No			SSE, SSE2, SSE3 Floating point Instructions
	"Virtualisation Error",			//	Fault		No			EPT Violations (only on certain processors)
	"Control Protection Exception", //	Fault		Yes			Branch faults
	"System Reserved 2",			//
	"System Reserved 3",			//
	"System Reserved 4",			//
	"System Reserved 5",			//
	"System Reserved 6",			//
	"System Reserved 7",			//
	"System Reserved 8",			//
	"System Reserved 9",			//
	"System Reserved 10",			//
	"System Reserved 11",			//
									// Interrupts 32-255 are User defined i.e non reserved. These are called by external interrupts or INT n
};

enum IntCodes {
	INT_ZERO_DIV,
	INT_DEBUG,
	INT_NMI,
	INT_BREAKPOINT,
	INT_OVERFLOW,
	INT_BOUND_EXCEED,
	INT_INVALID_OPCODE,
	INT_DEV_UNAVAILABLE,
	INT_DOUBLE_FAULT,
	INT_COPROC_SEG_OVERRUN,
	INT_INVALID_TSS,
	INT_SEG_NOT_PRESENT,
	INT_STACK_FAULT,
	INT_GEN_PROT_FAULT,
	INT_PAGE_FAULT,
	INT_x87_FPU = 16,
	INT_ALIGN_CHECK,
	INT_MACHINE_CHECK,
	INT_SIMD_FP,
	INT_VIRT_FAULT,
	INT_CONTROL_PROT_FAULT,
	INT_PIT = 32,
	INT_KEYBOARD,
	INT_CASCADE,
	INT_COM2,
	INT_COM1,
	INT_LPT2,
	INT_FLOPPY,
	INT_LPT1,
	INT_CMOS,
	INT_MOUSE = 44,
	INT_FPU,
	INT_PRIM_ATA,
	INT_AUX_ATA,
};

// Handles exception calls
void ExceptionHandler();
// Initialises the IDT
void InitIDT();
// Kernel Panic
void kpanic(IntStackFrame *frame);

void SetIDTDescriptor(uint8_t idx, void* isr, uint8_t attrs);

void InstallIRQHandler(uint32_t irq, void(*handler)(IntStackFrame* frame));

void UninstallIRQHandler(uint32_t irq);

void InitIRQ();

void PICRemap();

void PICAcknowledge(uint8_t interrupt);

uint8_t ReadScanCode();