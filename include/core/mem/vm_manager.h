#ifndef __KERNEL_VM_MANAGER_H_
#define __KERNEL_VM_MANAGER_H_

#define KERNEL_BASE		0xFFFFFFFF80000000
#define HIGH_HALF_OFFSET	0xFFFF800000000000

void *vm_phys_to_virt(void *phys_addr);
void *vm_virt_to_phys(void *virt_addr);

#endif
