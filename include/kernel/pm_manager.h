#ifndef __KERNEL_PM_MANAGER_H_
#define __KERNEL_PM_MANAGER_H_

#include <stdint.h>
#include <stdbool.h>


struct pm_bitmap {
	bool is_free;		/* is the page usable? (free)*/
	bool is_kernel_alloc;	/* is kernel allocated the page or is it reserved*/
}__attribute__((packed));

typedef struct pm_bitmap pm_bitmap_t;

struct pm_manager {
	pm_bitmap_t *bitmap;
	uint64_t total_pages;
	uint64_t usable_pages;
	uint64_t last_allocated_index;
	uint64_t bitmap_size;
}__attribute__((packed));

typedef struct pm_manager pm_manager_t;

void init_pm_manager(void);
void *pm_alloc_page(void);
int pm_free_page(void *address);
pm_manager_t *pm_get_manager(void);

#endif
