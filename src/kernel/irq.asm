section .text
bits 64

global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15


irq0:
	cli
	push 0
	push 0
	jmp irq_common_stub
irq1:
	cli
	push 0
	push 1
	jmp irq_common_stub
irq2:
	cli
	push 0
	push 2
	jmp irq_common_stub
irq3:
	cli
	push 0
	push 3
	jmp irq_common_stub
irq4:
	cli
	push 0
	push 4
	jmp irq_common_stub
irq5:
	cli
	push 0
	push 5
	jmp irq_common_stub
irq6:
	cli
	push 0
	push 6
	jmp irq_common_stub
irq7:
	cli
	push 0
	push 7
	jmp irq_common_stub
irq8:
	cli
	push 0
	push 8
	jmp irq_common_stub
irq9:
	cli
	push 0
	push 9
	jmp irq_common_stub
irq10:
	cli
	push 0
	push 10
	jmp irq_common_stub
irq11:
	cli
	push 0
	push 11
	jmp irq_common_stub
irq12:
	cli
	push 0
	push 12
	jmp irq_common_stub
irq13:
	cli
	push 0
	push 13
	jmp irq_common_stub
irq14:
	cli
	push 0
	push 14
	jmp irq_common_stub
irq15:
	cli
	push 0
	push 15
	jmp irq_common_stub


extern irq_handler

irq_common_stub:
	; Save all general purpose registers
	push rax
	push rbx
	push rcx
	push rdx
	push rsi
	push rdi
	push rbp
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
    
	; Save segment registers (64-bit mode uses 64-bit pushes)
	mov rax, ds
	push rax
	mov rax, es
	push rax
	mov rax, fs
	push rax
	mov rax, gs
	push rax
    
	; Align stack to 16 bytes before C call
	mov rbp, rsp
	and rsp, 0xFFFFFFFFFFFFFFF0  ; Align to 16 bytes

	; Load kernel data segment
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
    
	; Pass stack pointer as argument (System V AMD64 calling convention)
	mov rdi, rbp
    
	; Call C handler
	call irq_handler
    
	mov rsp, rbp
	; Restore segment registers
	pop rax
	mov gs, ax
	pop rax
	mov fs, ax
	pop rax
	mov es, ax
	pop rax
	mov ds, ax
    
	; Restore all general purpose registers
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rbp
	pop rdi
	pop rsi
	pop rdx
	pop rcx
	pop rbx
	pop rax
    
	; Clean up error code and interrupt number
	add rsp, 16
    
	; Return from interrupt
	iretq
