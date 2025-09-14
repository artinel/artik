#ifndef __CONSOLE_H_
#define __CONSOLE_H_

#include <stdint.h>
#include <font/psf.h>

struct console{
	uint32_t char_bg;	/* character background */
	uint32_t char_fg;	/* character foreground */
	uint32_t scr_bg;	/* screen background */
	uint16_t width;		/* screen width */
	uint16_t height;	/* screen height */
	uint16_t max_col;	/* maximum number of characters in a row */
	uint16_t max_row;	/* maximus number of characters in a column */
	uint16_t col;		/* current col position */
	uint16_t row;		/* current row position */
	uint32_t scanline;	/* bytes to pixels */
	psf2_t *font;		/* a pointer to the psf font data */
	uint16_t cursor_col;	/* current cursor x position*/
	uint16_t cursor_row;	/* current cursor y position */
};

void init_console(void);
void console_putchar(uint16_t ch);
void console_clear(void);
void console_set_background(uint32_t bg);
void console_set_foreground(uint32_t fg);
void console_paint_background(uint32_t bg);
void console_putchar_at(uint16_t ch, uint16_t col, uint16_t row);
struct console* console_get_self(void);

#endif
