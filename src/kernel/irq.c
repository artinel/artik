#include <kernel/irq.h>
#include <kernel/isr.h>
#include <kernel/idt.h>
#include <kernel/pic.h>
#include <io/ports.h>
#include <io/iox.h>
#include <stdlib.h>
#include <stdint.h>

extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);

static void *irq_routines[16] = {
	NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL
};

void irq_install_routine(uint8_t irq, void (*handler)(struct registers *regs)) {
	if (irq <= 15) {
		irq_routines[irq] = handler;
	}
}

void irq_uninstall_routine(uint8_t irq) {
	if (irq <= 15) {
		irq_routines[irq] = NULL;
	}
}

void init_irq(void) {
	idt_set_gate(32, (uint64_t) irq0, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(33, (uint64_t) irq1, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(34, (uint64_t) irq2, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(35, (uint64_t) irq3, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(36, (uint64_t) irq4, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(37, (uint64_t) irq5, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(38, (uint64_t) irq6, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(39, (uint64_t) irq7, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(40, (uint64_t) irq8, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(41, (uint64_t) irq9, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(42, (uint64_t) irq10, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(43, (uint64_t) irq11, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(44, (uint64_t) irq12, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(45, (uint64_t) irq13, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(46, (uint64_t) irq14, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
	idt_set_gate(47, (uint64_t) irq15, KERNEL_CS, ISR_NO_IST, ISR_GATE_INT, ISR_DPL_R0);
}

void irq_handler(struct registers *regs) {
	void (*handler)(struct registers *regs);
	uint8_t irq_index = regs->int_no - 32;
	handler = irq_routines[irq_index];
	if (handler != NULL) {
		handler(regs);
	}

	pic_send_eoi(irq_index);
}
