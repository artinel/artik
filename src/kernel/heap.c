#include <kernel/heap.h>
#include <kernel/pm_manager.h>
#include <kernel/vm_manager.h>
#include <libk/flags.h>
#include <stdint.h>
#include <stdlib.h>

static void *pages[32];
static uint8_t pages_count = 0;

void init_heap(void) {
	void *init_page = pm_alloc_page();

	/* no page found to allocated */
	if (init_page == NULL) {
		/* [TODO] panic the kernel*/
		return;
	}
	
	/* Add the initial page virtual address to the pages array */
	init_page = vm_phys_to_virt(init_page);
	pages[0] = init_page;
	pages_count++;

	/* Set the base header */
	heap_header_t *base_header = (heap_header_t *) init_page;
	base_header->prev_header = NULL;
	base_header->next_header = NULL;
	SET_FLAG(base_header->flags, HEAP_FREE);
}
