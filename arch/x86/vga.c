#include <kernel/vga.h>
#include <stdint.h>
#include <stdbool.h>

#define VGA_BUFFER_ADDR 0xB8000

static inline uint8_t color_combine(uint8_t bg, uint8_t fg);
static inline uint16_t char_combine(unsigned char c, uint8_t color);
static inline bool color_validate(uint8_t color);
static uint8_t vga_paint(uint8_t color, uint8_t type);
static void vga_scroll();

static uint16_t* vga_buffer;
static bool vga_is_init = false;
static uint8_t bg_color = VGA_COLOR_BLACK;
static uint8_t fg_color = VGA_COLOR_WHITE;
static uint8_t vga_row = 0;
static uint8_t vga_col = -1;

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
			vga_putchar(vga_buffer[row * VGA_MAX_COL + col]);
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

static void vga_scroll(){
	for(uint8_t r = 1; r < VGA_MAX_ROW + 1; r++){
		for(uint8_t c = 0; c < VGA_MAX_COL; c++){
			vga_putchar_at(vga_buffer[r * VGA_MAX_COL + c], r - 1, c);
		}
	}
	vga_row = VGA_MAX_ROW - 1;
	vga_col = -1;
}

void vga_init(){
	if(vga_is_init == false){
		vga_buffer = (uint16_t*)VGA_BUFFER_ADDR;
		vga_is_init = true;
	}
}

uint8_t vga_putchar(unsigned char c){
	if(vga_is_init == true){
		
		if(vga_row == VGA_MAX_ROW){
			vga_scroll();
		}
	
		if(c == '\n'){
			vga_col = -1;
			vga_row++;
		}else if(c == '\t'){
			for(uint8_t i = 0; i < VGA_TAB_SIZE; i++){
				vga_putchar(' ');
			}
		}else{
			vga_col++;
			uint8_t color = color_combine(bg_color, fg_color);
			vga_buffer[vga_row * VGA_MAX_COL + vga_col] = char_combine(c, color);
		}

		if(vga_col == VGA_MAX_COL - 1){
			vga_col = -1;
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
	if((row < VGA_MAX_ROW) && (col < VGA_MAX_COL)){
		uint8_t tmp_col = vga_col;
		uint8_t tmp_row = vga_row;

		vga_col = col - 1;
		vga_row = row;
		uint8_t res = vga_putchar(c);

		vga_col = tmp_col;
		vga_row = tmp_row;

		return res;
	}

	return 1;
}

uint8_t vga_draw_rect(uint8_t width, uint8_t height, uint8_t col, uint8_t row){
	if((width >= 1 && width <= VGA_MAX_COL && height >= 1 && height <= VGA_MAX_ROW) && 
			(row < VGA_MAX_ROW && col < VGA_MAX_COL)){
		if(width <= (VGA_MAX_COL - col) && height <= (VGA_MAX_ROW - row)){
			uint8_t tmp_col = col;
			for(uint8_t h = 0; h < height; h++){
				for(uint8_t w = 0; w < width; w++){
					vga_putchar_at(' ', row, col);
					col++;
				}
				col = tmp_col;
				row++;
			}

		}else{
			return 1;
		}	
	}
	return 1;
}

void vga_clear(){
	for(uint8_t r = 0; r < VGA_MAX_ROW; r++){
		for(uint8_t c = 0; c < VGA_MAX_COL; c++){
			vga_putchar_at('\0', r, c);
		}
	}

	vga_col = -1;
	vga_row = 0;
}
