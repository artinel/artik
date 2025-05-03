#include <kernel/vga.h>
#include <stdint.h>
#include <stdbool.h>

#define VGA_BUFFER_ADDR 0xB8000

static uint16_t* vga_buffer;
static bool vga_is_init = false;

static uint8_t color_combine(uint8_t bg, uint8_t fg){
	return (uint8_t) fg | (uint8_t) bg << 4;
}

static uint16_t char_combine(unsigned char c, uint8_t color){
	return (uint16_t) c | (uint16_t) color << 8;
}

void vga_init(){
	if(vga_is_init == false){
		vga_buffer = (uint16_t*)VGA_BUFFER_ADDR;
	}
}

void vga_putchar(unsigned char c, uint8_t bg, uint8_t fg){
	uint8_t color = color_combine(bg, fg);
	*vga_buffer = char_combine(c, color);
	vga_buffer++;
}
