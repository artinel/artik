#include <kernel/heap.h>
#include <kernel/pm_manager.h>
#include <kernel/vm_manager.h>
#include <kernel/paging.h>
#include <libk/stdio.h>
#include <libk/flags.h>
#include <stdint.h>
#include <stdlib.h>

#define TOTAL_PAGES	32

static void *pages[TOTAL_PAGES];
static uint8_t pages_count = 0;
static uint8_t header_size = 0;

static uint8_t heap_alloc_page(uint8_t index);

void init_heap(void) {
	header_size = sizeof(heap_header_t);

	uint8_t res = heap_alloc_page(0);
	
	if (res != HEAP_ALLOC_OK) {
		/* [TODO] panic the kernel*/
		return;
	}
}

static uint8_t heap_alloc_page(uint8_t index) {
	if (index >= TOTAL_PAGES) {
		return HEAP_ALLOC_INVL_INDEX;
	}

	if (pages[index] != 0) {
		return HEAP_ALLOC_INVL_INDEX;
	}

	void *page = pm_alloc_page();

	if (page == NULL) {
		return HEAP_ALLOC_FAIL;
	}

	page = vm_phys_to_virt(page);
	pages[index] = page;
	pages_count++;

	heap_header_t *base_header = (heap_header_t *) page;
	base_header->prev_header = NULL;
	base_header->next_header = NULL;
	SET_FLAG(base_header->flags, HEAP_FREE);
	base_header->size = PAGE_SIZE - header_size;
	
	return HEAP_ALLOC_OK;
}

void *heap_alloc(uint16_t size) {
	if (size > PAGE_SIZE - header_size) {
		return NULL;
	}
	
	heap_header_t *header = NULL;
	for (uint8_t i = 0; i < pages_count; i++) {
		header = pages[i];

		while (header != NULL) {
			if (CHECK_FLAG(header->flags, HEAP_FREE)) {
				if (header->size == size) {
					UNSET_FLAG(header->flags, HEAP_FREE);
					return header + header_size;
				}

				if (header->size >= size + header_size) {
					UNSET_FLAG(header->flags, HEAP_FREE);
					heap_header_t *h = (heap_header_t *)(header + 
						header_size + size);

					h->prev_header = (void *) header;
					h->next_header = header->next_header;
					header->next_header = (void *) h;
					if (h->next_header != NULL) {
						heap_header_t *tmp = 
							(heap_header_t*) h->next_header;
						tmp->prev_header = (void *) h;
					}
					SET_FLAG(h->flags, HEAP_FREE);
					h->size = header->size - (size + header_size);
					header->size = size;

					return header + header_size;
				}
			}
			header = header->next_header;
		}

		if ((i + 1) == pages_count) {
			if (heap_alloc_page(i + 1) != HEAP_ALLOC_OK) {
				return NULL;
			}
		}
	}

	return NULL;
}

void heap_print_map(void) {
	for (uint8_t i = 0; i < pages_count; i++) {
		heap_header_t *header = pages[i];

		while (header != NULL) {
			printf("---------------------------------\n");
			printf("PAGE INDEX : %ud\n", i);
			printf("PAGE ADDRESS : 0x%ux\n", pages[i]);
			printf("--- HEADERS ---\n");
			printf("HEADER ADDRESS : 0x%ux\n", header);
			printf("HEADER PREVIOUS ADDRESS : 0x%ux\n", header->prev_header);
			printf("HEADER NEXT ADDRESS : 0x%ux\n", header->next_header);
			printf("HEADER SIZE : %ud\n", header->size);
			if (CHECK_FLAG(header->flags, HEAP_FREE)) {
				printf("HEADER STATE : FREE\n");
			} else {
				printf("HEADER STATE : ALLOCATED\n");
			}
			printf("---------------------------------\n");
			
			header = header->next_header;
		}
	}
}
