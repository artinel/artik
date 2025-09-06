#ifndef __VIDEO_TTY_H_
#define __VIDEO_TTY_H_

#ifdef __ARCH_x86_

#include "../../arch/x86/driver/vga/vga.h"

#define tty_init() vga_init()
#define tty_putchar(c) vga_putchar(c)
#define tty_set_bg(bg) vga_set_bg(bg)
#define tty_set_fg(fg) vga_set_fg(fg)
#define tty_paint_bg(bg) vga_paint_bg(bg)
#define tty_paint_fg(fg) vga_paint_fg(fg)
#define tty_putchar_at(c, row, col) vga_putchar_at(c, row, col)

#endif

#endif
