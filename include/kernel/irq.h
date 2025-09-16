#ifndef __KERNEL_IRQ_H_
#define __KERNEL_IRQ_H_

#include <stdint.h>
#include <kernel/isr.h>

void init_irq(void);
void irq_install_routine(uint8_t irq, void (*handler)(struct registers *regs));
void irq_uninstall_routine(uint8_t irq);

#endif
