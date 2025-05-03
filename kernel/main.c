#include <kernel/vga.h>

void kernel_main(void){
	vga_init();
	vga_putchar('M', VGA_COLOR_RED, VGA_COLOR_GREEN);
}
