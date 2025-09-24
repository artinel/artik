#include <core/mem/pm_manager.h>
#include <core/mem/memmap.h>
#include <core/mem/paging.h>
#include <core/mem/vm_manager.h>
#include <stdlib.h>
#include <stdint.h>
#include <libk/flags.h>

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
	pm_manager.bitmap_size = pm_manager.total_pages * sizeof(pm_bitmap_t);

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
		/* Seta ll flags to 0(Not free) */
		pm_manager.bitmap[i].flags = 0;
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
				SET_FLAG(pm_manager.bitmap[page].flags, PM_FLAG_FREE);
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
	
		if (CHECK_FLAG(pm_manager.bitmap[i].flags, PM_FLAG_FREE)) {
			/* Mark page as allocated */
			UNSET_FLAG(pm_manager.bitmap[i].flags, PM_FLAG_FREE);
			SET_FLAG(pm_manager.bitmap[i].flags, PM_FLAG_KERNEL);
			pm_manager.last_allocated_index = i + 1;
			pm_manager.usable_pages--;
			return (void *)(i * PAGE_SIZE);
		}
	}

	/* Search from the beginnig if needed*/
	for (uint64_t i = 0; i < pm_manager.last_allocated_index; i++) {
		if (CHECK_FLAG(pm_manager.bitmap[i].flags, PM_FLAG_FREE)) {
			/* Mark page as allocated */
			UNSET_FLAG(pm_manager.bitmap[i].flags, PM_FLAG_FREE);
			SET_FLAG(pm_manager.bitmap[i].flags, PM_FLAG_KERNEL);
			pm_manager.last_allocated_index = i + 1;
			pm_manager.usable_pages--;
			return (void *) (i * PAGE_SIZE);
		}
	}

	/* Out of memory */
	return NULL;
}

static void *pm_alloc_multi_search(uint64_t start_index, uint64_t end_index, 
		uint32_t count) {

	bool is_enough = false;
	for (uint64_t i = start_index; i < end_index; i++) {

		if (CHECK_FLAG(pm_manager.bitmap[i].flags, PM_FLAG_FREE)) {
			for (uint32_t j = 0; j < count - 1; j++) {
				uint64_t index = i + j + 1;
				if(!CHECK_FLAG(pm_manager.bitmap[index].flags, 
							PM_FLAG_FREE)) {
					is_enough = false;		
					break;
				}
				is_enough = true;
			}
			if (is_enough) {
				for (uint32_t k = 0; k < count; k++) {
					uint64_t index = i + k;
					UNSET_FLAG(pm_manager.bitmap[index].flags,
							PM_FLAG_FREE);
			
					SET_FLAG(pm_manager.bitmap[index].flags,
							PM_FLAG_KERNEL);

					pm_manager.last_allocated_index = index + 1;
					pm_manager.usable_pages--;

				}

				return (void *)(i * PAGE_SIZE);
			}
		}	
	}

	return NULL;

}

void *pm_alloc_multi_page(uint32_t count) {
	if (count > pm_manager.usable_pages) {
		return NULL;
	}

	void *res = pm_alloc_multi_search(pm_manager.last_allocated_index, 
			pm_manager.total_pages, count);

	if (res == NULL) {
		res = pm_alloc_multi_search(0, pm_manager.last_allocated_index, count);
	}

	return res;

}

uint8_t pm_free_page(void *address) {
	uint64_t page = (uint64_t) address / PAGE_SIZE;

	if (page >= pm_manager.total_pages) {
		return PM_FREE_PAGE_INVL;
	}

	if (CHECK_FLAG(pm_manager.bitmap[page].flags, PM_FLAG_FREE)) {
		return PM_FREE_PAGE_NALLOC;
	}

	if (!CHECK_FLAG(pm_manager.bitmap[page].flags, PM_FLAG_KERNEL)) {
		return PM_FREE_PAGE_NKERNEL;
	}

	pm_manager.usable_pages++;

	SET_FLAG(pm_manager.bitmap[page].flags, PM_FLAG_FREE);
	UNSET_FLAG(pm_manager.bitmap[page].flags, PM_FLAG_KERNEL);

	return PM_FREE_PAGE_OK;
}

uint8_t pm_free_multi_page(void *address, uint32_t count) {
	
	void *addr = address;
	
	for (uint32_t i = 0; i < count; i++) {
		uint8_t res  = pm_free_page(addr);
		if (res != PM_FREE_PAGE_OK) {
			return res;
		}
		addr += PAGE_SIZE;
	}

	return PM_FREE_PAGE_OK;
}

pm_manager_t *pm_get_manager(void) {
	return &pm_manager;
}
