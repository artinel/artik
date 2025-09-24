#ifndef __KERNEL_MEMMAP_H_
#define __KERNEL_MEMMAP_H_

#include <stdint.h>

#define MEMMAP_USABLE                 	0x0
#define MEMMAP_RESERVED               	0x1
#define MEMMAP_ACPI_RECLAIMABLE       	0x2
#define MEMMAP_ACPI_NVS               	0x3
#define MEMMAP_BAD_MEMORY             	0x4
#define MEMMAP_BOOTLOADER_RECLAIMABLE 	0x5
#define MEMMAP_EXECUTABLE_AND_MODULES 	0x6
#define MEMMAP_FRAMEBUFFER            	0x7

struct memmap_entry {
	uint64_t base;
	uint64_t length;
	uint64_t type;
	uint64_t unused;
}__attribute__((packed));

struct memmap {
	uint64_t entry_count;
	struct memmap_entry **entries;
}__attribute__((packed));

typedef struct memmap_entry memmap_entry_t;
typedef struct memmap memmap_t;

void init_memmap(void);
memmap_entry_t *memmap_get_entry(uint64_t index);
uint64_t memmap_get_entry_count(void);

#endif
