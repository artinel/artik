#ifndef __KERNEL_CPUID_H_
#define __KERNEL_CPUID_H_

#include <stdint.h>

struct cpuid_regs {
	uint32_t eax;
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;
};

typedef struct cpuid_regs cpuid_regs_t;

void cpuid(uint32_t leaf, uint32_t subleaf, cpuid_regs_t *regs);

#endif
