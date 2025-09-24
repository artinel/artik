#ifndef __KERNEL_IDT_H_
#define __KERNEL_IDT_H_

#define KERNEL_CS	0x28
#define KERNEL_DS	0x30

void init_idt(void);
void idt_set_gate(uint8_t index, uint64_t offset, uint16_t selector, 
		uint8_t ist, uint8_t gate_type, uint8_t dpl);


#endif
