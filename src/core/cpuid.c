#include <core/cpuid.h>
#include <stdint.h>
#include <libk/stdio.h>

void cpuid(uint32_t leaf, uint32_t subleaf, cpuid_regs_t *regs) {
	asm volatile("cpuid"
			: "=a"(regs->eax), "=b"(regs->ebx), 
			  "=c"(regs->ecx), "=d"(regs->edx)
			: "a"(leaf), "c"(subleaf)
			: "memory");
}
