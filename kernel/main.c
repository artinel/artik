#include <kernel/vga.h>

static const char* hello = "Hello World!!";

static void wait(){
	for(int i = 0; i < 199900000; i++){}
}

void kernel_main(void){
	vga_init();
	vga_set_fg(VGA_COLOR_BLUE);
	vga_paint_bg(VGA_COLOR_WHITE);

	for(uint8_t c = 'A'; c <= 'Z'; c++){
		wait();
		vga_putchar(c);
		vga_putchar(c);

		vga_putchar(c);
		vga_putchar(c);
		vga_putchar(c);
		vga_putchar(c);
		vga_putchar(c);
		vga_putchar('\n');
	}

	for(uint8_t c = 'X'; c <= 'Z'; c++){
		wait();
		vga_putchar(c);
		vga_putchar(c);
		vga_putchar('\n');
	}

}
