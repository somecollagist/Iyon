#include "interrupts.h"

#include <types.h>
#include <drivers/terminal.h>

char digits[] = {
	'0', '1', '2', '3',
	'4', '5', '6', '7',
	'8', '9', 'A', 'B',
	'C', 'D', 'E', 'F'
};

char buf_cs[19];
char buf_ss[19];
char buf_rflags[19];

char buf_rax[19];
char buf_rbx[19];
char buf_rcx[19];
char buf_rdx[19];
char buf_rbp[19];
char buf_rsp[19];
char buf_rdi[19];
char buf_rsi[19];

char buf_r8[19];
char buf_r9[19];
char buf_r10[19];
char buf_r11[19];
char buf_r12[19];
char buf_r13[19];
char buf_r14[19];
char buf_r15[19];

extern const char* kpart;

static inline void kp_toHexString(char* buf, uint64_t num)
{
	buf[0] = '0';
	buf[1] = 'x';

	for(int x = 0; x < 16; x++)
		buf[2+x] = digits[((num >> ((15-x)*4)) & 0xF)];

	buf[18] = '\0';
}

#define kp_print(s) print(s, WHITE, RED)
#define MAXFRAMES 4

void kpanic(IntStackFrame* frame)
{
	StackFrame* stack;
	asm volatile("movq %%rbp, %0" : "=g"(stack)::"memory");

	InitTerminal();
	for(int y = 0; y < term_height; y++)
	{
		for(int x = 0; x < term_width; x++)
		{
			kp_print(" ");
		}
	}

	InitTerminal();
	char* message[] = {
		"      ,---'~-_       Something's gone wrong...              ", "\n",
		"      |~-_    '~-,                                          ", "\n",
		"    I |   ~-+---'|   +---+  +---+  |    |  ---+---  +----  |", "\n",
		"    Y |     |    |   |   |  |   |  ||   |     |     |      |", "\n",
		"    O |     |    |   |   |  |   |  | |  |     |     |      |", "\n",
		"    N |     | :( |   +---+  |---|  |  | |     |     |      |", "\n",
		"      |     |    |   |      |   |  |   ||     |     |      |", "\n",
		"      ~-_   |    |   |      |   |  |    |  ---+---  +----  0", "\n",
		"         ~-_|,---'                                          ", "\n",
		"\n",
		" ==== IYON KERNEL PANIC", "\n",
		" Exception Message: ", IntMsgs[frame->int_num], "\n",
		"\n",
		" Registers:\n",
		"  cs:  ", buf_cs,  "  ss:  ", buf_ss,  "  rflags: ", buf_rflags, "\n",
		"\n",
		"  rax: ", buf_rax, "  rbx: ", buf_rbx, "\n",
		"  rcx: ", buf_rcx, "  rdx: ", buf_rdx, "\n",
		"  rbp: ", buf_rbp, "  rsp: ", buf_rsp, "\n",
		"  rdi: ", buf_rdi, "  rsi: ", buf_rsi, "\n",
		"\n",
		"  r8:  ", buf_r8,  "  r9:  ", buf_r9, "\n",
		"  r10: ", buf_r10, "  r11: ", buf_r11, "\n",
		"  r12: ", buf_r12, "  r13: ", buf_r13, "\n",
		"  r14: ", buf_r14, "  r15: ", buf_r15, "\n",
		"\n",
		" Stack Trace:", "\n"
	};

	kp_toHexString(buf_cs, frame->cs);
	kp_toHexString(buf_ss, frame->ss);
	kp_toHexString(buf_rflags, frame->rflags);

	kp_toHexString(buf_rax, frame->rax);
	kp_toHexString(buf_rbx, frame->rbx);
	kp_toHexString(buf_rcx, frame->rcx);
	kp_toHexString(buf_rdx, frame->rdx);
	kp_toHexString(buf_rbp, frame->rbp);
	kp_toHexString(buf_rsp, frame->rsp);
	kp_toHexString(buf_rdi, frame->rdi);
	kp_toHexString(buf_rsi, frame->rsi);

	kp_toHexString(buf_r8, frame->r8);
	kp_toHexString(buf_r9, frame->r9);
	kp_toHexString(buf_r10, frame->r10);
	kp_toHexString(buf_r11, frame->r11);
	kp_toHexString(buf_r12, frame->r12);
	kp_toHexString(buf_r13, frame->r13);
	kp_toHexString(buf_r14, frame->r14);
	kp_toHexString(buf_r15, frame->r15);


	for(int x = 0; x < sizeof(message)/sizeof(char*); x++)
	{
		kp_print(message[x]);
	}

	// Note for the lost soul who found their way here, maybe check this over? There was an issue on this crashing and thowing Gen. Prot. Faults
	for(int x = 0; stack && x < MAXFRAMES; x++)
	{
		kp_print("  ");
		char buf[19];
		kp_toHexString(buf, stack->rip);
		kp_print(buf);
		kp_print("\n");
		stack = stack->rbp;	// Here!
	}

	asm volatile("cli");
	asm volatile("hlt");

	for(;;);
}