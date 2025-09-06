#include <video/tty.h>
#include <libk/stdio.h>
#include <kernel/idt.h>

void main(void) {
	tty_init();
	
	puts("Starting kernel...");

	puts("Initializing IDT...");
	init_idt();

	puts("Kernel is ready...");

	while (1) {}
}
