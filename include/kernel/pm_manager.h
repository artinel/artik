#ifndef __KERNEL_PM_MANAGER_H_
#define __KERNEL_PM_MANAGER_H_

#include <stdint.h>
#include <stdbool.h>

#define PM_FREE_PAGE_OK		0x00
#define PM_FREE_PAGE_INVL	0x01
#define PM_FREE_PAGE_NALLOC	0x02
#define PM_FREE_PAGE_NKERNEL	0x03

#define PM_FLAG_FREE		1
#define PM_FLAG_KERNEL		2

struct pm_bitmap {
	uint8_t flags;
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
uint8_t pm_free_page(void *address);
pm_manager_t *pm_get_manager(void);
void *pm_alloc_multi_page(uint32_t count);
uint8_t pm_free_multi_page(void *address, uint32_t count);

#endif
