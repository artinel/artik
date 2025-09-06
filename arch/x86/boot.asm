MBALIGN equ 1 << 0
MEMINFO equ 1 << 1
MBFLAGS equ MBALIGN | MEMINFO
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + MBFLAGS)

section .multiboot
align 4
	dd MAGIC
	dd MBFLAGS
	dd CHECKSUM	

section .bss
align 16
stack_bottom:
resb 16384
stack_top:

CODE_SEG equ 0x08
DATA_SEG equ 0x10

section .text
global _start:function (_start.end - _start)
_start:
	mov esp, stack_top

	;; Call C function to initialize GDT	
	extern init_gdt
	call init_gdt

	extern gdt_descriptor
	lgdt [gdt_descriptor]

	;; Load GDT
	lgdt [gdt_descriptor]

	;; Setup Segment Registers
	jmp CODE_SEG:.set_cs

.set_cs:
	mov ax, DATA_SEG	;; Load data segment selector
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	extern main
	call main
	
	cli

.hang : 
	hlt
	jmp .hang
.end:
