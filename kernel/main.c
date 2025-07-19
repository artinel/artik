#include <video/vga.h>

static uint32_t str_len(const char *str) {
	uint32_t size = 0;
	while (*str++) {
		size++;
	}

	return size;
}

void kernel_main(void){
	const char* version = "Artik Version 0.0.1\n";
	
	vga_init();
	vga_set_fg(VGA_COLOR_GREEN);
	vga_paint_bg(VGA_COLOR_BLACK);

	uint32_t len = str_len(version);
	
	for (uint32_t i = 0; i < len; i++) {
		vga_putchar(version[i]);
	}
}
