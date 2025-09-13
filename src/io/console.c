#include <stdint.h>
#include <io/console.h>
#include <io/framebuffer.h>
#include <font/psf.h>
#include <font/default.psf.h>

#define PIXEL uint32_t
#define TAB_SIZE 8

struct console{
	uint32_t background;	/* character background */
	uint32_t foreground;	/* character foreground */
	uint16_t width;		/* screen width */
	uint16_t height;	/* screen height */
	uint16_t max_col;	/* maximum number of characters in a row */
	uint16_t max_row;	/* maximus number of characters in a column */
	uint16_t x;		/* current x position */
	uint16_t y;		/* current y position */
	uint32_t scanline;	/* bytes to pixels */
	psf2_t *font;		/* a pointer to the psf font data */
};

static struct console console;

void init_console(){
	console.background = 0x000000;	/* set background to black */
	console.foreground = 0xFFFFFF;	/* set foreground to white */
	console.width = fb_get_width();	/* get width from framebuffer */
	console.height = fb_get_height();	/* get height from framebuffer */
	console.font = (psf2_t *) default_psf; /* set the font to default */
	console.max_col = console.width / console.font->width;
	console.max_row = console.height / console.font->height;
	console.x = 0;
	console.y = 0;
	console.scanline = fb_get_pitch() / sizeof(PIXEL);
}

void console_putchar(uint16_t ch) {
	
	/* tab support */
	if (ch == '\t') {
		console.x += TAB_SIZE;
		if (console.x > console.max_col - 1) {
			int diff = console.x - (console.max_col - 1);
			console.x = diff;
			console.y++;
		}
		return;
	}

	/* newline support */
	if (ch == '\n') {
		console.y++;
		console.x = 0;
		return;
	}

	/* carriage return support */
	if (ch == '\r') {
		console.x = 0;
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
	uint32_t start_x = console.x * console.font->width;
	uint32_t start_y = console.y * console.font->height;

	uint32_t color = console.background;

	for (uint32_t y = 0; y < console.font->height; y++) {
		for (uint32_t x = 0; x < console.font->width; x++) {
			int byte_index = x / 8;
			int bit_index = 7 - (x % 8);
			int bit_mask = 1 << bit_index;

			/* get the pixel value */
			uint32_t pixel_set = (glyph[y * bytes_per_line + 
					byte_index] & bit_mask) != 0;

			if (pixel_set == 0) {
				color = console.background;
			} else {
				color = console.foreground;
			}

			/* calculate framebuffer position */
			uint32_t fb_x = start_x + x;
			uint32_t fb_y = start_y + y;

			fb_putpixel(color, fb_x, fb_y);
		}
	}

	if (console.x < console.max_col - 1) {
		console.x++;
	} else {
		console.y++;
		console.x = 0;
	}
}
