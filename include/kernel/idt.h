#ifndef __KERNEL_IDT_H_
#define __KERNEL_IDT_H_

/* because limine setup our gdt the selectors are as follow. refer to limine 
 * documentation for more information */
#define KERNEL_CS	0x50
#define KERNEL_DS	0x60

void init_idt(void);

#endif
