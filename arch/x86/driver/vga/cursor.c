#include <stdint.h>
#include <io/iox.h>
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
