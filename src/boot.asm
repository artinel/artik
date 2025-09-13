section .text
bits 64

global _start
extern main
_start:
	mov rsp, stack_top
	cld

	call main
.halt:
	hlt
	jmp .halt


section .bss
align 16
stack_bottom:
resb 16384
stack_top:
