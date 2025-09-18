#include <kernel/mem.h>
#include <limine.h>

__attribute__((used, section(".limine_requests")))
static volatile struct limine_memmap_request memmap_req = {
	.id = LIMINE_MEMMAP_REQUEST,
	.revision = 3
};

static memmap_t memmap;

void init_memmap(void) {
	memmap.entry_count = memmap_req.response->entry_count;
	memmap.entries = (memmap_entry_t **)memmap_req.response->entries;
}
