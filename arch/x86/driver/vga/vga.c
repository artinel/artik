#include <video/vga.h>
#include <stdint.h>
#include <stdbool.h>
#include <libk/ret.h>
#include "cursor.h"

#define VGA_BUFFER_ADDR 0xB8000

static inline uint8_t color_combine(uint8_t bg, uint8_t fg);
static inline uint16_t char_combine(unsigned char c, uint8_t color);
static inline bool color_validate(uint8_t color);
static uint8_t vga_paint(uint8_t color, uint8_t type);
static void vga_scroll();

struct vga {
	uint16_t *buffer;
	bool is_init;
	uint8_t bg;
	uint8_t fg;
	uint8_t row;
	uint8_t col;
}vga;

static inline uint8_t color_combine(uint8_t bg, uint8_t fg){
	return (uint8_t) fg | (uint8_t) bg << 4;
}

static inline uint16_t char_combine(unsigned char c, uint8_t color){
	return (uint16_t) c | (uint16_t) color << 8;
}

static inline bool color_validate(uint8_t color){
	return (color <= VGA_COLOR_WHITE) ? true : false;
}

static uint8_t vga_paint(uint8_t color, uint8_t type){
	if(color_validate(color) == true){
		uint8_t col = -1;
		uint8_t row = 0;
		uint8_t tmp_col = vga.col;
		uint8_t tmp_row = vga.row;
		
		vga.col = 0;
		vga.row = 0;

		if(type == VGA_PAINT_BG){
			vga.bg = color;
		}else{
			vga.fg = color;
		}

		while(row < VGA_MAX_ROW){
			col++;
			vga_putchar(vga.buffer[row * VGA_MAX_COL + col]);
			if(col == VGA_MAX_COL - 1){
				col = -1;
				row++;
			}
		}

		vga.col = tmp_col;
		vga.row = tmp_row;
		return RET_SUCCESS;
	}

	return RET_FAILURE;
}

static void vga_scroll(){
	for(uint8_t r = 1; r < VGA_MAX_ROW + 1; r++){
		for(uint8_t c = 0; c < VGA_MAX_COL; c++){
			vga_putchar_at(vga.buffer[r * VGA_MAX_COL + c], r - 1, c);
		}
	}
	vga.row = VGA_MAX_ROW - 1;
	vga.col = -1;
}

void vga_init(){
	if(vga.is_init == false){
		vga.buffer = (uint16_t*)VGA_BUFFER_ADDR;
		vga.is_init = true;
		vga.bg = VGA_COLOR_BLACK;
		vga.fg = VGA_COLOR_WHITE;
		vga.row = 0;
		vga.col = -1;

		/* Make the cursor fill the entire character area */
		enable_cursor(0, 15);
	}
}

uint8_t vga_putchar(unsigned char c){
	if(vga.is_init == true){
		
		if(vga.row == VGA_MAX_ROW){
			vga_scroll();
		}
	
		if(c == '\n'){
			vga.col = -1;
			vga.row++;
		}else if(c == '\t'){
			for(uint8_t i = 0; i < VGA_TAB_SIZE; i++){
				vga_putchar(' ');
			}
		}else{
			vga.col++;
			uint8_t color = color_combine(vga.bg, vga.fg);
			vga.buffer[vga.row * VGA_MAX_COL + vga.col] = char_combine(c, color);
			update_cursor(vga.row, vga.col + 1);
		}

		if(vga.col == VGA_MAX_COL - 1){
			vga.col = -1;
			vga.row++;
		}		

		return RET_SUCCESS;
	}else{
		return RET_FAILURE;
	}
}

uint8_t vga_set_bg(uint8_t color){
	if(color_validate(color) == true){
		vga.bg = color;
		return RET_SUCCESS;
	}else{
		return RET_FAILURE;
	}
}

uint8_t vga_set_fg(uint8_t color){
	if(color_validate(color) == true){
		vga.fg = color;
		return RET_SUCCESS;
	}else{
		return RET_FAILURE;
	}
}

uint8_t vga_paint_bg(uint8_t color){
	return vga_paint(color, VGA_PAINT_BG);
}

uint8_t vga_paint_fg(uint8_t color){
	return vga_paint(color, VGA_PAINT_FG);
}

uint8_t vga_putchar_at(unsigned char c, uint8_t row, uint8_t col){
	if((row < VGA_MAX_ROW) && (col < VGA_MAX_COL)){
		uint8_t tmp_col = vga.col;
		uint8_t tmp_row = vga.row;

		vga.col = col - 1;
		vga.row = row;
		uint8_t res = vga_putchar(c);

		vga.col = tmp_col;
		vga.row = tmp_row;

		return res;
	}

	return RET_FAILURE;
}

void vga_clear(){
	for(uint8_t r = 0; r < VGA_MAX_ROW; r++){
		for(uint8_t c = 0; c < VGA_MAX_COL; c++){
			vga_putchar_at('\0', r, c);
		}
	}

	vga.col = -1;
	vga.row = 0;
}
