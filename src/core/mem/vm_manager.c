#include <core/mem/vm_manager.h>
#include <limine.h>

__attribute__((used, section(".limine_requests")))
static struct limine_hhdm_request hhdm_req = {
	.id = LIMINE_HHDM_REQUEST,
	.revision = 0
};

void *vm_phys_to_virt(void *phys_addr) {
	void *virt_addr = (void *) (phys_addr + hhdm_req.response->offset);
	return virt_addr;
}

void *vm_virt_to_phys(void *virt_addr) {
	void *phys_addr = (void *) (virt_addr - hhdm_req.response->offset);
	return phys_addr;
}
