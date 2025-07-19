#include <video/vga.h>

static const char* hello = "Hello World!!";

static void wait(){
	for(int i = 0; i < 199900000; i++){}
}

static uint32_t str_len(const char *str) {
	uint32_t size = 0;
	while (*str++) {
		size++;
	}

	return size;
}

void kernel_main(void){
	vga_init();
	vga_set_fg(VGA_COLOR_GREEN);
	vga_paint_bg(VGA_COLOR_BLACK);

	uint32_t len = str_len(hello);
	int col = (VGA_MAX_COL / 2) - (len / 2);
	int row = VGA_MAX_ROW / 2;

	for (int i = 0; i < len; i++) {
		vga_putchar_at(hello[i], row, col++);
	}
}
