#include <libk/stdint.h>
#include "gdt.h"

struct gdt_entry {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
}__attribute__((packed));


struct gdt_descriptor{
	uint16_t limit;
	uint32_t base;
}__attribute__((packed));

// External declarations for assembly use
extern struct gdt_descriptor gdt_descriptor;

void gdt_set_entry(int index, uint32_t base, uint32_t limit, 
		uint8_t access, uint8_t granularity);

struct gdt_entry gdt_entries[3];
struct gdt_descriptor gdt_descriptor;

void gdt_set_entry(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt_entries[index].base_low = (base & 0xFFFF);
    gdt_entries[index].base_middle = (base >> 16) & 0xFF;
    gdt_entries[index].base_high = (base >> 24) & 0xFF;
    
    gdt_entries[index].limit_low = (limit & 0xFFFF);
    gdt_entries[index].granularity = ((limit >> 16) & 0x0F) | (granularity & 0xF0);
    
    gdt_entries[index].access = access;
}

void init_gdt(void) {
    gdt_descriptor.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gdt_descriptor.base = (uint32_t)&gdt_entries;
    
    // Null descriptor (required)
    gdt_set_entry(0, 0, 0, 0, 0);
    
    // Code segment: base=0, limit=0xFFFFF, 4KB granularity, 32-bit
    gdt_set_entry(1, 0, 0xFFFFF, 0x9A, 0xCF);
    
    // Data segment: base=0, limit=0xFFFFF, 4KB granularity, 32-bit
    gdt_set_entry(2, 0, 0xFFFFF, 0x92, 0xCF);
}
