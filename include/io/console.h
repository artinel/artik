#ifndef __CONSOLE_H_
#define __CONSOLE_H_

#include <stdint.h>

void init_console(void);
void console_putchar(uint16_t ch);
void console_clear(void);
void console_set_background(uint32_t bg);
void console_set_foreground(uint32_t fg);
void console_paint_background(uint32_t bg);

#endif
