#include <kernel/pm_manager.h>
#include <kernel/memmap.h>
#include <kernel/paging.h>
#include <kernel/vm_manager.h>
#include <stdlib.h>
#include <stdint.h>

static pm_manager_t pm_manager;

void init_pm_manager(void) {

	/* Total memory */
	uint64_t total_mem = 0;

	/* Total usable memory */
	uint64_t total_use_mem = 0;

	uint64_t memmap_count = memmap_get_entry_count();

	memmap_entry_t *memmap_entry = 0;
	
	/* Calculate the total usable memory and the highest address */
	for (uint64_t i = 0; i < memmap_count; i++) {
		memmap_entry = memmap_get_entry(i);

		if (memmap_entry->type == MEMMAP_USABLE) {
			total_use_mem += memmap_entry->length;
		}

		total_mem += memmap_entry->length;
	}

	pm_manager.total_pages = total_mem / PAGE_SIZE;
	pm_manager.bitmap_size = pm_manager.total_pages * sizeof(pm_manager_t);

	uint64_t bitmap_addr = 0;

	/* Find a suitable location for bitmap (First Fit) */
	for (uint64_t i = 0; i < memmap_count; i++) {
		memmap_entry = memmap_get_entry(i);

		if (memmap_entry->type == MEMMAP_USABLE && 
				memmap_entry->length >= pm_manager.bitmap_size) {
		
			bitmap_addr = memmap_entry->base;
			memmap_entry->base += pm_manager.bitmap_size;
			memmap_entry->length -= pm_manager.bitmap_size;
			break;
		}
	}


	/* Out of memory */
	if (bitmap_addr == 0) {
		/* [TODO] Panic the kernel because no suitable location found */
	}

	/* Set bitmap address */
	pm_manager.bitmap = (pm_bitmap_t *) (bitmap_addr + HIGH_HALF_OFFSET);

	/* Initialize all pages as allocated */
	for (uint64_t i = 0; i < pm_manager.total_pages; i++) {
		pm_manager.bitmap[i].is_free = false;
		pm_manager.bitmap[i].is_kernel_alloc = false;
	}

	/* Mark all usable pages as free */
	pm_manager.usable_pages = 0;

	for (uint64_t i = 0; i < memmap_count; i++) {
		memmap_entry = memmap_get_entry(i);
		if (memmap_entry->type == MEMMAP_USABLE) {
			/* Find how many pages this usable region is */
			uint64_t page_start = memmap_entry->base / PAGE_SIZE;
			uint64_t page_end = (memmap_entry->base + 
					memmap_entry->length) / PAGE_SIZE;

			/* Mark each page as free in bitmap */
			for (uint64_t page = page_start; page < page_end; page++) {
				pm_manager.bitmap[page].is_free = true;
				pm_manager.usable_pages++;
			}
		}
	} 

	pm_manager.last_allocated_index = 0;
}

/* Allocate a physical page */
void *pm_alloc_page(void) {
	/* Search for a free page from the last allocated page index */
	for (uint64_t i = pm_manager.last_allocated_index; 
			i < pm_manager.total_pages; i++) {
	
		if (pm_manager.bitmap[i].is_free) {
			/* Mark page as allocated */
			pm_manager.bitmap[i].is_free = false;
			pm_manager.bitmap[i].is_kernel_alloc = true;
			pm_manager.last_allocated_index = i + 1;
			pm_manager.usable_pages--;
			return (void *)(i * PAGE_SIZE);
		}
	}

	/* If last allocated index is 0 then we have already searched all
	 * the pages and we did not find a suitable place. */
	if (pm_manager.last_allocated_index == 0) {
		/* Out of memory */
		return NULL;
	}

	/* Search from the beginnig if needed*/
	for (uint64_t i = 0; i < pm_manager.last_allocated_index; i++) {
		if (pm_manager.bitmap[i].is_free) {
			/* Mark page as allocated */
			pm_manager.bitmap[i].is_free = false;
			pm_manager.bitmap[i].is_kernel_alloc = true;
			pm_manager.last_allocated_index = i + 1;
			pm_manager.usable_pages--;
			return (void *) (i * PAGE_SIZE);
		}
	}

	/* Out of memory */
	return NULL;
}

int pm_free_page(void *address) {
	uint64_t page = (uint64_t) address / PAGE_SIZE;

	if (page >= pm_manager.total_pages) {
		return PM_FREE_PAGE_INVL;
	}

	if (pm_manager.bitmap[page].is_free) {
		return PM_FREE_PAGE_NALLOC;
	}

	if (pm_manager.bitmap[page].is_kernel_alloc == false) {
		return PM_FREE_PAGE_NKERNEL;
	}

	pm_manager.usable_pages++;
	pm_manager.bitmap[page].is_free = true;
	pm_manager.bitmap[page].is_kernel_alloc = false;

	return PM_FREE_PAGE_OK;
}

pm_manager_t *pm_get_manager(void) {
	return &pm_manager;
}
