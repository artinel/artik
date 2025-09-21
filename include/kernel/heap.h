#ifndef __KERNEL_HEAP_H_
#define __KERNEL_HEAP_H_

#include <stdint.h>

#define HEAP_FREE		0x01

#define HEAP_ALLOC_OK		0x00
#define HEAP_ALLOC_INVL_COUNT	0x01
#define HEAP_ALLOC_FAIL		0x02

#define HEAP_FREE_OK		0x00
#define HEAP_FREE_INVL_ADDR	0x01
#define HEAP_FREE_NALOC		0x02

#define HEAP_PAGE_DALLOC	0x01

struct heap_header {
	void *prev_header;
	uint8_t flags;
	uint32_t size;
	void *next_header;
}__attribute__((packed));

struct heap_page {
	uint8_t flags;
	uint16_t count;
	void *addr;
}__attribute__((packed));

typedef struct heap_header heap_header_t;
typedef struct heap_page heap_page_t;

void init_heap(void);
void *heap_alloc(uint32_t size);
void heap_print_map(void);
uint8_t heap_free(void *address);

#endif
