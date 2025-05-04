#include <kernel/vga.h>

void kernel_main(void){
	vga_init();
	vga_set_bg(VGA_COLOR_BLUE);
	vga_set_fg(VGA_COLOR_GREEN);
	for(int i = 0; i < 120; i++){
		vga_putchar('M');
	}
}
