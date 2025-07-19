#ifndef _KERNEL_VGA_H
#define _KERNEL_VGA_H

#include <stdint.h>

#define VGA_MAX_ROW 25
#define VGA_MAX_COL 80
#define VGA_TAB_SIZE 8

enum vga_color{
	VGA_COLOR_BLACK,
	VGA_COLOR_BLUE,
	VGA_COLOR_GREEN,
	VGA_COLOR_CYAN,
	VGA_COLOR_RED,
	VGA_COLOR_MAGENTA,
	VGA_COLOR_BROWN,
	VGA_COLOR_LIGHT_GRAY,
	VGA_COLOR_DARK_GRAY,
	VGA_COLOR_LIGHT_BLUE,
	VGA_COLOR_LIGHT_GREEN,
	VGA_COLOR_LIGHT_CYAN,
	VGA_COLOR_LIGHT_RED,
	VGA_COLOR_LIGHT_MAGENTA,
	VGA_COLOR_LIGHT_BROWN,
	VGA_COLOR_WHITE,
};

enum vga_paint_type {
	VGA_PAINT_BG,
	VGA_PAINT_FG
};

void vga_init();
uint8_t vga_putchar(unsigned char c);
uint8_t vga_set_bg(uint8_t color);
uint8_t vga_set_fg(uint8_t color);
uint8_t vga_paint_bg(uint8_t color);
uint8_t vga_paint_fg(uint8_t color);
uint8_t vga_putchar_at(unsigned char c, uint8_t row, uint8_t col);
void vga_clear();

#endif
