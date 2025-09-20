#ifndef __KERNEL_HEAP_H_
#define __KERNEL_HEAP_H_

#include <stdint.h>

#define HEAP_FREE		0x01

#define HEAP_ALLOC_OK		0x00
#define HEAP_ALLOC_INVL_INDEX	0x01
#define HEAP_ALLOC_FAIL		0x02

struct heap_header {
	void *prev_header;
	uint8_t flags;
	uint16_t size;
	void *next_header;
};

typedef struct heap_header heap_header_t;

void init_heap(void);
void *heap_alloc(uint16_t size);
void heap_print_map(void);

#endif
