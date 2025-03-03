#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <kernel/vga.h>

void tty_init();
void tty_putchar(unsigned char c);
void tty_write(const char* data, size_t size);
void tty_set_bg(enum vga_color color);
void tty_set_fg(enum vga_color color);

#endif
