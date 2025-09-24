section .text
bits 64

global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

;;; Division by zero
isr0:
	cli
	push 0
	push 0
	jmp isr_common_stub

;;; Debug
isr1:
	cli
	push 0
	push 1
	jmp isr_common_stub


;;; Not maskable interrupt
isr2:
	cli
	push 0
	push 2
	jmp isr_common_stub


;;; Break point
isr3:
	cli
	push 0
	push 3
	jmp isr_common_stub


;;; Into detected overflow
isr4:
	cli
	push 0
	push 4
	jmp isr_common_stub


;;; Out of bounds
isr5:
	cli
	push 0
	push 5
	jmp isr_common_stub


;;; Invalid opcode
isr6:
	cli
	push 0
	push 6
	jmp isr_common_stub


;;; No coprocessor
isr7:
	cli
	push 0
	push 7
	jmp isr_common_stub


;;; Double fault
isr8:
	cli
	push 8
	jmp isr_common_stub


;;; Coprocessor segment
isr9:
	cli
	push 0
	push 9
	jmp isr_common_stub


;;; Bad TSS
isr10:
	cli
	push 10
	jmp isr_common_stub


;;; Segment not present
isr11:
	cli
	push 11
	jmp isr_common_stub


;;; Stack fault
isr12:
	cli
	push 12
	jmp isr_common_stub


;;; General protection fault
isr13:
	cli
	push 13
	jmp isr_common_stub


;;; Page fault
isr14:
	cli
	push 14
	jmp isr_common_stub


;;; Unknown interrupt
isr15:
	cli
	push 0
	push 15
	jmp isr_common_stub


;;; Coprocessor fault
isr16:
	cli
	push 0
	push 16
	jmp isr_common_stub


;;; Alignment check
isr17:
	cli
	push 0
	push 17
	jmp isr_common_stub


;;; Machine check
isr18:
	cli
	push 0
	push 18
	jmp isr_common_stub


;;; Reserved
isr19:
	cli
	push 0
	push 19
	jmp isr_common_stub


;;; Reserved
isr20:
	cli
	push 0
	push 20
	jmp isr_common_stub


;;; Reserved
isr21:
	cli
	push 0
	push 21
	jmp isr_common_stub


;;; Reserved
isr22:
	cli
	push 0
	push 22
	jmp isr_common_stub


;;; Reserved
isr23:
	cli
	push 0
	push 23
	jmp isr_common_stub


;;; Reserved
isr24:
	cli
	push 0
	push 24
	jmp isr_common_stub


;;; Reserved
isr25:
	cli
	push 0
	push 25
	jmp isr_common_stub


;;; Reserved
isr26:
	cli
	push 0
	push 26
	jmp isr_common_stub


;;; Reserved
isr27:
	cli
	push 0
	push 27
	jmp isr_common_stub


;;; Reserved
isr28:
	cli
	push 0
	push 28
	jmp isr_common_stub


;;; Reserved
isr29:
	cli
	push 0
	push 29
	jmp isr_common_stub


;;; Reserved
isr30:
	cli
	push 0
	push 30
	jmp isr_common_stub


;;; Reserved
isr31:
	cli
	push 0
	push 31
	jmp isr_common_stub

extern isr_fault_handler

isr_common_stub:
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
	call isr_fault_handler
    
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
