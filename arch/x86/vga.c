#include <kernel/vga.h>
#include <stdint.h>
#include <stdbool.h>

#define VGA_BUFFER_ADDR 0xB8000

static uint16_t* vga_buffer;
static bool vga_is_init = false;
static uint8_t bg_color = VGA_COLOR_BLACK;
static uint8_t fg_color = VGA_COLOR_WHITE;

static inline uint8_t color_combine(uint8_t bg, uint8_t fg){
	return (uint8_t) fg | (uint8_t) bg << 4;
}

static inline uint16_t char_combine(unsigned char c, uint8_t color){
	return (uint16_t) c | (uint16_t) color << 8;
}

void vga_init(){
	if(vga_is_init == false){
		vga_buffer = (uint16_t*)VGA_BUFFER_ADDR;
	}
}

uint8_t vga_putchar(unsigned char c){
	if(vga_is_init == true){
		uint8_t color = color_combine(bg_color, fg_color);
		*vga_buffer = char_combine(c, color);
		vga_buffer++;
		return 0;
	}else{
		return 1;
	}
}

uint8_t vga_set_bg(uint8_t color){
	if(color >= VGA_COLOR_BLACK && color <= VGA_COLOR_WHITE){
		bg_color = color;
		return 0;
	}else{
		return 1;
	}
}

uint8_t vga_set_fg(uint8_t color){
	if(color >= VGA_COLOR_BLACK && color <= VGA_COLOR_WHITE){
		fg_color = color;
		return 0;
	}else{
		return 1;
	}
}
