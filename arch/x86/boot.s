.set ALIGN,     1<<0
.set MEMINFO,   1<<1
.set FLAGS,     MEMINFO | ALIGN
.set MAGIC,     0x1BADB002
.set CHECKSUM,  -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .text
.global _start
.type _start, @function
_start:
        movl $stack_top, %esp
        #TODO: add global constructor support
        call kernel_main
        cli
1:      hlt
        jmp 1b

.size _start, . - _start
        
