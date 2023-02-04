extern bootboot
extern init
extern main

global _start

_start:
	mov eax, 1
	cpuid
	shr ebx, 24
	cmp bx, [bootboot + 0xC]
	je init		; stuff to be run on a single processor
	jmp main	; the main kernel shenanigans