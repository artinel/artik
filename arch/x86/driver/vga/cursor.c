#include <libk/stdint.h>
#include "vga.h"
#include "cursor.h"
#include "vga_ports.h"
#include "vga_regs.h"
#include "../../iox.h"

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end) {
	outb(VGA_CTRL_PORT, VGA_COLOR_PLANE);
	outb(VGA_CTRL_WR_PORT, 
			(inb(VGA_CTRL_WR_PORT) & VGA_CGA)
			| cursor_start);

	outb(VGA_CTRL_PORT, VGA_MODE_CTRL);
	outb(VGA_CTRL_WR_PORT, 
			(inb(VGA_CTRL_WR_PORT) & VGA_EXT_COLOR)
			| cursor_end);

}

void update_cursor(uint8_t row, uint8_t col) {
	uint16_t pos = row * VGA_MAX_COL + col;
	outb(VGA_CTRL_PORT, VGA_COLOR_PLANE_ENABLER);
	outb(VGA_CTRL_WR_PORT, (uint8_t) (pos & 0xFF));
	outb(VGA_CTRL_PORT, VGA_MEM_MODE);
	outb(VGA_CTRL_WR_PORT, (uint8_t) ((pos >> 8) & 0xFF));
}

void disable_cursor() {
	outb(VGA_CTRL_PORT, VGA_COLOR_PLANE);
	outb(VGA_CTRL_WR_PORT, VGA_COLOR_PLANE_DISABLER);
}

uint16_t get_cursor_pos() {
	uint16_t pos = 0;
	outb(VGA_CTRL_PORT, VGA_COLOR_PLANE_ENABLER);
	pos |= inb(VGA_CTRL_WR_PORT);
	outb(VGA_CTRL_PORT, VGA_MEM_MODE);
	pos |= inb((uint16_t)inb(VGA_CTRL_WR_PORT)) << 8;
	return pos;
}
