#include <libk/stdint.h>
#include <libk/string.h>
#include "idt.h"

struct idt_entry {
	uint16_t base_low;
	uint16_t selector;
	uint8_t zero;
	uint8_t flags;
	uint8_t base_high;
}__attribute__((packed));

struct idt_ptr {
	uint16_t limit;
	uint32_t base;
}__attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

extern void load_idt();

static void idt_set_gate(uint8_t index, uint32_t base, 
		uint16_t selector, uint8_t flags) {

	idt[index].base_low = (base & 0xFFFF);
	idt[index].base_high = (base >> 16) & 0xFFFF;
	idt[index].selector = selector;
	idt[index].zero = 0;
	idt[index].flags = flags;

}

void init_idt(void){
	idtp.limit = sizeof(idt) - 1;
	idtp.base = (uint32_t) &idt;

	memset(&idt, 0, sizeof(idt));

	// Add new ISRs here using idt_set_gate

	load_idt();
}
