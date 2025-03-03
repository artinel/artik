#ifndef _KERNEL_VGA_H
#define _KERNEL_VGA_H

#include <stddef.h>

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

void vga_init();
void vga_putchar(unsigned char c);
void vga_write(const char*, size_t size);
void vga_set_bg(enum vga_color);
void vga_set_fg(enum vga_color);

#endif
