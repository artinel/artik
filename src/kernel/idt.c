#include <stdint.h>
#include <kernel/idt.h>
#include <libk/string.h>
#include <kernel/isr.h>

#define IDTS_LENGTH	256

struct idt_descriptor {
	uint16_t offset_low;	/* offset bits 0...15 */
	uint16_t selector;	/* segment selector */
	uint8_t ist;		/* bits 0...2 holds interrupt stack table 
				 * offset, the rest are zero */
	uint8_t type_attr;	/* gate type, dpl and p fields */
	uint16_t offset_mid;	/* offset bits 16...31 */
	uint32_t offset_high;	/* offset bits 32...63*/
	uint32_t zero;		/* reserved */
}__attribute__((packed));

struct idtr {
	uint16_t limit;
	uint64_t base;
}__attribute__((packed));

typedef struct idt_descriptor idt_descriptor_t;
typedef struct idtr idtr_t;

static idt_descriptor_t idts[IDTS_LENGTH];
idtr_t idtr;

extern void load_idt(void);

void idt_set_gate(uint8_t index, uint64_t offset, uint16_t selector, 
		uint8_t ist, uint8_t gate_type, uint8_t dpl) {

	idts[index].zero = 0;
	
	idts[index].selector = selector;

	idts[index].offset_low = (offset & 0xFFFF);
	idts[index].offset_mid = (offset >> 16) & 0xFFFF;
	idts[index].offset_high = (offset >> 32) & 0xFFFFFFFF;

	idts[index].ist = (ist & 0x07);
	
	idts[index].type_attr = (1 << 7) | ((dpl & 0x03) << 5) | 
		(gate_type & 0x0F);
}

void init_idt(void) {
	idtr.limit = sizeof(idts) - 1;
	idtr.base = (uint64_t) &idts;
	
	memset(&idts, 0, sizeof(idts));

	load_idt();
}
