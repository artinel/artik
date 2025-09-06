#include <video/tty.h>
#include <libk/stdio.h>

void main(void) {
	tty_init();
	
	puts("Starting kernel...");
	puts("Kernel is ready...");

	while (1) {}
}
