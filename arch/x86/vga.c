#include <kernel/vga.h>
#include <stdint.h>
#include <stdbool.h>

#define VGA_BUFFER_ADDR 0xB8000
#define VGA_MAX_ROW 25
#define VGA_MAX_COL 80

static inline uint8_t color_combine(uint8_t bg, uint8_t fg);
static inline uint16_t char_combine(unsigned char c, uint8_t color);
static inline bool color_validate(uint8_t color);
static uint8_t vga_paint(uint8_t color, uint8_t type);

static uint16_t* vga_buffer;
static bool vga_is_init = false;
static uint8_t bg_color = VGA_COLOR_BLACK;
static uint8_t fg_color = VGA_COLOR_WHITE;
static uint8_t vga_row = 0;
static uint8_t vga_col = 0;

static inline uint8_t color_combine(uint8_t bg, uint8_t fg){
	return (uint8_t) fg | (uint8_t) bg << 4;
}

static inline uint16_t char_combine(unsigned char c, uint8_t color){
	return (uint16_t) c | (uint16_t) color << 8;
}

static inline bool color_validate(uint8_t color){
	return (color >= VGA_COLOR_BLACK && color <= VGA_COLOR_WHITE) ? true : false;
}

static uint8_t vga_paint(uint8_t color, uint8_t type){
	if(color_validate(color) == true){
		uint8_t col = -1;
		uint8_t row = 0;
		uint8_t tmp_col = vga_col;
		uint8_t tmp_row = vga_row;
		
		vga_col = 0;
		vga_row = 0;
		if(type == 0){
			bg_color = color;
		}else{
			fg_color = color;
		}

		while(row < VGA_MAX_ROW){
			col++;
			vga_putchar_at(vga_buffer[row * VGA_MAX_COL + col], row, col);
			if(col == VGA_MAX_COL - 1){
				col = -1;
				row++;
			}
		}

		vga_col = tmp_col;
		vga_row = tmp_row;
		return 0;
	}

	return 1;
}



void vga_init(){
	if(vga_is_init == false){
		vga_buffer = (uint16_t*)VGA_BUFFER_ADDR;
		vga_is_init = true;
	}
}

uint8_t vga_putchar(unsigned char c){
	if(vga_is_init == true){
		uint8_t color = color_combine(bg_color, fg_color);
		vga_buffer[vga_row * VGA_MAX_COL + vga_col] = char_combine(c, color);
		vga_col++;

		if(vga_col == VGA_MAX_COL - 1){
			vga_col = 0;
			vga_row++;
		}

		return 0;
	}else{
		return 1;
	}
}

uint8_t vga_set_bg(uint8_t color){
	if(color_validate(color) == true){
		bg_color = color;
		return 0;
	}else{
		return 1;
	}
}

uint8_t vga_set_fg(uint8_t color){
	if(color_validate(color) == true){
		fg_color = color;
		return 0;
	}else{
		return 1;
	}
}

uint8_t vga_paint_bg(uint8_t color){
	return vga_paint(color, 0);
}

uint8_t vga_paint_fg(uint8_t color){
	return vga_paint(color, 1);
}

uint8_t vga_putchar_at(unsigned char c, uint8_t row, uint8_t col){
	if((row >= 0 && row < VGA_MAX_ROW) && (col >= 0 && col < VGA_MAX_COL)){
		vga_col = col;
		vga_row = row;
		return vga_putchar(c);
	}

	return 1;
}
