#ifndef __X86_VGA_CURSOR_H
#define __X86_VGA_CURSOR_H

#include <libk/stdint.h>

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void update_cursor(uint8_t row, uint8_t col);
void disable_cursor();
uint16_t get_cursor_pos();

#endif
