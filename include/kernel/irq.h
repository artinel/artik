#ifndef __KERNEL_IRQ_H_
#define __KERNEL_IRQ_H_

#include <stdint.h>
#include <kernel/isr.h>

void init_irq(void);
void irq_install_handler(uint8_t irq, void (*handler)(struct registers *regs));
void irq_uninstall_handler(uint8_t irq);

#endif
