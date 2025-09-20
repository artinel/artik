#ifndef __KERNEL_HEAP_H_
#define __KERNEL_HEAP_H_

#include <stdint.h>

#define HEAP_FREE	0x01

struct heap_header {
	void *prev_header;
	uint8_t flags;
	void *next_header;
};

typedef struct heap_header heap_header_t;

void init_heap(void);

#endif
