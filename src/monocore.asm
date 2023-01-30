bits 64

global RunOn1Core:
	cmp [ebp + 8], 0x00000001	; guard
	je CoreRun
CoreReturn:
	ret

CoreRun:
	mov [ebp + 8], 1
	call [ebp + 16]		; prc
	jmp CoreReturn
