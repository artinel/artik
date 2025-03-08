#include <stdio.h>
#include <stdlib.h>

__attribute__((__noreturn__))
void abort(void){
#if defined(__is_libk)
	printk("Kernel panic : abort()\n");
	asm volatile("hlt");
#else
	printk("abort()\n");
#endif
	while(1){}
	__builtin_unreachable();
}
