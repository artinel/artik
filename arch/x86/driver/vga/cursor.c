#include <stdint.h>
#include <io/iox.h>
#include <video/vga.h>
#include "cursor.h"
#include "vga_ports.h"
#include "vga_regs.h"

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end) {
	outb(VGA_CTRL_PORT, VGA_COLOR_PLANE_REG);
	outb(VGA_CTRL_WR_PORT, 
			(inb(VGA_CTRL_WR_PORT) & VGA_CGA_REG)
			| cursor_start);

	outb(VGA_CTRL_PORT, VGA_MODE_CTRL_REG);
	outb(VGA_CTRL_WR_PORT, 
			(inb(VGA_CTRL_WR_PORT) & VGA_EXT_COLOR_REG)
			| cursor_end);

}

void update_cursor(uint8_t row, uint8_t col) {
	uint16_t pos = row * VGA_MAX_COL + col;
	outb(VGA_CTRL_PORT, VGA_COLOR_PLANE_ENABLER);
	outb(VGA_CTRL_WR_PORT, (uint8_t) (pos & 0xFF));
	outb(VGA_CTRL_PORT, VGA_MEM_MODE_REG);
	outb(VGA_CTRL_WR_PORT, (uint8_t) ((pos >> 8) & 0xFF));
}
