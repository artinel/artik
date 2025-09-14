#include <kernel/isr.h>
#include <kernel/idt.h>
#include <libk/stdio.h>
#include <io/console.h>
#include <stdint.h>

extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);

static char *exception_msg[] = {
	"Divide By Zero",
	"Debug",
	"Non Maskable Interrupt",
	"Breakpoint",
	"Into Detected Overflow",
	"Out Of Bounds",
	"Invalid Opcode",
	"No Coprocessor",
	"Double Fault",
	"Coprocessor Segment Overrun",
	"Bad TSS",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	"Unknown Interrupt",
	"Coprocessor Fault",
	"Alignment Check",
	"Machine Check",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
};

void init_isr(void) {
	idt_set_gate(0, (uint64_t)isr0, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(1, (uint64_t)isr1, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(2, (uint64_t)isr2, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(3, (uint64_t)isr3, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(4, (uint64_t)isr4, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(5, (uint64_t)isr5, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(6, (uint64_t)isr6, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(7, (uint64_t)isr7, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(8, (uint64_t)isr8, KERNEL_CS, ISR_IST_DF, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(9, (uint64_t)isr9, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(10, (uint64_t)isr10, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(11, (uint64_t)isr11, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(12, (uint64_t)isr12, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(13, (uint64_t)isr13, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(14, (uint64_t)isr14, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(15, (uint64_t)isr15, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(16, (uint64_t)isr16, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(17, (uint64_t)isr17, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(18, (uint64_t)isr18, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(19, (uint64_t)isr19, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(20, (uint64_t)isr20, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(21, (uint64_t)isr21, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(22, (uint64_t)isr22, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(23, (uint64_t)isr23, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(24, (uint64_t)isr24, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(25, (uint64_t)isr25, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(26, (uint64_t)isr26, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(27, (uint64_t)isr27, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(28, (uint64_t)isr28, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(29, (uint64_t)isr29, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(30, (uint64_t)isr30, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(31, (uint64_t)isr31, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
}

void isr_fault_handler(struct registers *regs) {
	if (regs->int_no < 32) {
		console_paint_background(0xFF0000);
		console_set_background(0xFF0000);
		console_set_foreground(0xFFFFFF);
		puts("Exception : ");
		puts(exception_msg[regs->int_no]);
		putchar('\n');
		puts("System halted!!!\n");

		while(1) {}
	}
}
