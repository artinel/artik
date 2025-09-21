#include <kernel/heap.h>
#include <kernel/pm_manager.h>
#include <kernel/vm_manager.h>
#include <kernel/paging.h>
#include <libk/stdio.h>
#include <libk/flags.h>
#include <stdint.h>
#include <stdlib.h>

#define TOTAL_PAGES	32

static heap_page_t *pages;
static uint8_t pages_count = 0;
static uint8_t header_size = 0;

static uint8_t heap_alloc_page(uint32_t count);

void init_heap(void) {
	header_size = sizeof(heap_header_t);

	/* Allocate a page for storing the list of pages  */
	pages = vm_phys_to_virt(pm_alloc_page());

	/* Allocate the initial page */
	uint8_t res = heap_alloc_page(1);
	
	if (res != HEAP_ALLOC_OK) {
		/* [TODO] panic the kernel*/
		return;
	}
}

static uint8_t heap_alloc_page(uint32_t count) {
	void *page = NULL;

	if (count == 1) {
		page = pm_alloc_page();
	} else if (count > 1) {
		page = pm_alloc_multi_page(count);
	} else {
		return HEAP_ALLOC_INVL_COUNT;
	}

	if (page == NULL) {
		return HEAP_ALLOC_FAIL;
	}

	uint32_t index = pages_count;
	for (uint32_t i = 0; i < pages_count; i++) {
		if (CHECK_FLAG(pages[i].flags, HEAP_PAGE_DALLOC)) {
			index = i;
			break;
		}
	}

	page = vm_phys_to_virt(page);
	pages[index].addr = page;
	pages[index].count = count;
	pages[index].flags = 0;
	pages_count++;

	heap_header_t *base_header = (heap_header_t *) page;
	base_header->prev_header = NULL;
	base_header->next_header = NULL;
	SET_FLAG(base_header->flags, HEAP_FREE);
	base_header->size = (PAGE_SIZE * count) - header_size;
	
	return HEAP_ALLOC_OK;
}

void *heap_alloc(uint32_t size) {
	if (size > (uint32_t)PAGE_SIZE - header_size) {
		uint32_t count = (size + header_size) / PAGE_SIZE;
		count++;
		if (heap_alloc_page(count) != HEAP_ALLOC_OK) {
			return NULL;
		}
	}
	
	heap_header_t *header = NULL;
	for (uint8_t i = 0; i < pages_count; i++) {
		header = pages[i].addr;

		while (header != NULL && !CHECK_FLAG(pages[i].flags, HEAP_PAGE_DALLOC)) {
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
					
					void *ptr = (void *)header + header_size;

					return ptr;
				}
			}
			header = header->next_header;
		}

		if ((i + 1) == pages_count) {
			if (heap_alloc_page(1) != HEAP_ALLOC_OK) {
				return NULL;
			}
		}
	}

	return NULL;
}

void heap_print_map(void) {
	for (uint8_t i = 0; i < pages_count; i++) {
		heap_header_t *header = pages[i].addr;

		while (header != NULL) {
			printf("---------------------------------\n");
			printf("PAGE INDEX : %ud\n", i);
			printf("PAGE ADDRESS : 0x%ux\n", pages[i].addr);
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

uint8_t heap_free(void *address) {
	if (address == NULL) {
		return HEAP_FREE_INVL_ADDR;
	}

	heap_header_t *header = (heap_header_t *)(address - header_size);
	
	if (CHECK_FLAG(header->flags, HEAP_FREE)) {
		return HEAP_FREE_NALOC;
	}

	SET_FLAG(header->flags, HEAP_FREE);

	heap_header_t *next = (heap_header_t *)header->next_header;
	if (next != NULL && CHECK_FLAG(next->flags, HEAP_FREE)) {
		header->next_header = next->next_header;
	
		heap_header_t *next_tmp = header->next_header;

		if (next_tmp != NULL) {
			next_tmp->prev_header = header;
		}
		
		header->size += next->size + header_size;

		next->next_header = NULL;
		next->prev_header = NULL;
	}

	heap_header_t *prev = (heap_header_t *) header->prev_header;
	if (prev != NULL && CHECK_FLAG(prev->flags, HEAP_FREE)) {
		prev->next_header = header->next_header;

		heap_header_t *next_tmp = prev->next_header;

		if (next_tmp != NULL) {
			next_tmp->prev_header = prev;
		}

		prev->size += header->size + header_size;


		header->next_header = NULL;
		header->prev_header = NULL;
	}

	for(uint8_t i = 1; i < pages_count; i++) {
		if (CHECK_FLAG(pages[i].flags, HEAP_PAGE_DALLOC)) {
			continue;
		}

		heap_header_t *base = pages[i].addr;

		if(CHECK_FLAG(base->flags, HEAP_FREE) && base->next_header == NULL) {
			uint8_t res = 0;
			if (pages[i].count == 1) {
				res = pm_free_page(vm_virt_to_phys(pages[i].addr));
			} else {
				res = pm_free_multi_page(vm_virt_to_phys(pages[i].addr),
						pages[i].count);
			}

			if (res != PM_FREE_PAGE_OK) {
				return HEAP_FREE_NALOC;
			}

			SET_FLAG(pages[i].flags, HEAP_PAGE_DALLOC);
			pages[i].addr = NULL;
			pages[i].count = 0;
		}
	}
	
	return HEAP_FREE_OK;
}
