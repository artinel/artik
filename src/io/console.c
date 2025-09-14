#include <stdint.h>
#include <io/console.h>
#include <io/framebuffer.h>
#include <font/psf.h>
#include <font/default.psf.h>
#include <libk/string.h>

/* [TODO] Implement redrawing character at cursor position when we have malloc */

#define PIXEL uint32_t
#define TAB_SIZE 8

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

static struct console console;

static void console_draw_cursor(void);
static void console_clear_cursor(void);
static void console_scroll(void);
static void console_move_cursor(uint16_t x, uint16_t y);

void init_console(){
	console.char_bg = 0x000000;	/* set background to black */
	console.char_fg = 0xFFFFFF;	/* set foreground to white */
	console.scr_bg = console.char_bg;
	console.width = fb_get_width();	/* get width from framebuffer */
	console.height = fb_get_height();	/* get height from framebuffer */
	console.font = (psf2_t *) default_psf; /* set the font to default */
	console.max_col = console.width / console.font->width;
	console.max_row = console.height / console.font->height;
	console.col = 0;
	console.row = 0;
	console.scanline = fb_get_pitch() / sizeof(PIXEL);
	console.cursor_col = console.col;
	console.cursor_row = console.row;

	console_draw_cursor();
}


void console_putchar(uint16_t ch) {
	
	/* clear the last position of cursor */
	console_clear_cursor();

	/* tab support */
	if (ch == '\t') {
		console.col += TAB_SIZE;
		if (console.col > console.max_col - 1) {
			int diff = console.col - (console.max_col - 1);
			console.col = diff;
			console.row++;
		}
		console_move_cursor(console.col + 1, console.row);	

		return;
	}

	/* newline support */
	if (ch == '\n') {
		console.row++;
		console.col = 0;
		if (console.row >= console.max_row) {
			console_scroll();
		}

		console_move_cursor(console.col, console.row);
		return;
	}

	/* carriage return support */
	if (ch == '\r') {
		console.col = 0;
		console_move_cursor(console.col, console.row);
		return;
	}

	/* check for invalid font */
	if (console.font->magic != PSF2_FONT_MAGIC) {
		return;		
	}

	/* ensure the character is within bound */
	if (ch >= console.font->num_glyph) {
		ch = 0;	/* use the first glyph if invalid character */
	}

	/* calculate bytes per line */
	int bytes_per_line = (console.font->width + 7) / 8;

	/* make a pointer to the desired glyph */
	uint8_t *glyph = (uint8_t *) console.font + console.font->header_size;
	glyph += ch * console.font->bytes_per_glyph;

	/* calculate starting position in framebuffer*/
	uint32_t start_x = console.col * console.font->width;
	uint32_t start_y = console.row * console.font->height;

	uint32_t color = console.char_bg;

	for (uint32_t y = 0; y < console.font->height; y++) {
		for (uint32_t x = 0; x < console.font->width; x++) {
			int byte_index = x / 8;
			int bit_index = 7 - (x % 8);
			int bit_mask = 1 << bit_index;

			/* get the pixel value */
			uint32_t pixel_set = (glyph[y * bytes_per_line + 
					byte_index] & bit_mask) != 0;

			if (pixel_set == 0) {
				color = console.char_bg;
			} else {
				color = console.char_fg;
			}

			/* calculate framebuffer position */
			uint32_t fb_x = start_x + x;
			uint32_t fb_y = start_y + y;

			fb_putpixel(color, fb_x, fb_y);
		}
	}

	if (console.col < console.max_col - 1) {
		console.col++;
	} else {
		console.row++;
		console.col = 0;
		if (console.row >= console.max_row) {
			console_scroll();
		}
	}

	console_move_cursor(console.col, console.row);
}

static void console_scroll(void){
	uint32_t *fb = fb_get_buffer();
	uint32_t scanline = console.scanline;
	uint32_t font_height = console.font->height;

	/* calculate memory regions */
	uint32_t bytes_per_pixel = sizeof(PIXEL);
	uint32_t scroll_size = (console.height - font_height) * scanline *
		bytes_per_pixel;

	uint32_t clear_size = font_height * scanline * bytes_per_pixel;

	memmove(fb, fb + (font_height * scanline), scroll_size);

	// clear the bottom area
	uint32_t *clear_start = fb + ((console.height - font_height) * scanline);

	for (uint32_t i = 0; i < clear_size / sizeof(PIXEL); i++) {
		clear_start[i] = console.scr_bg;
	}

	console.col = 0;
	console.row = console.max_row - 1;
}

void console_clear(void) {
	uint32_t *fb = fb_get_buffer();
	
	for (int i = 0; i < console.width * console.height; i++) {
		fb[i] = console.scr_bg;
	}

	console.col = 0;
	console.row = 0;
}

void console_set_background(uint32_t bg) {
	console.char_bg = bg;
}

void console_set_foreground(uint32_t fg) {
	console.char_fg = fg;
}

void console_paint_background(uint32_t bg) {
	uint32_t *fb = fb_get_buffer();
	console.scr_bg = bg;

	for (int i = 0; i < console.width * console.height; i++) {
		fb[i] = bg;
	}

	console.col = 0;
	console.row = 0;
}


static void console_draw_cursor(void) {
	uint32_t start_x = console.cursor_col * console.font->width;
	uint32_t start_y = console.cursor_row * console.font->height;

	for (uint32_t y = 0; y < console.font->height; y++) {
		for (uint32_t x = 0; x < console.font->width; x++) {
			fb_putpixel(console.char_fg, x + start_x, 
					y + start_y);	
		}
	}
}

static void console_clear_cursor(void) {
	uint32_t start_x = console.cursor_col * console.font->width;
	uint32_t start_y = console.cursor_row * console.font->height;

	for (uint32_t y = 0; y < console.font->height; y++) {
		for (uint32_t x = 0; x < console.font->width; x++) {
			fb_putpixel(console.scr_bg, x + start_x, 
					y + start_y);	
		}
	}
}

static void console_move_cursor(uint16_t col, uint16_t row) {
	console.cursor_col = col;
	console.cursor_row = row;
	console_draw_cursor();
}

void console_putchar_at(uint16_t ch, uint16_t col, uint16_t row) {
	if (col >= console.max_col || row >= console.max_row) {
		return;
	}

	console.col = col;
	console.row = row;
	console_putchar(ch);
}
