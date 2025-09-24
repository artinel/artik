#include <stdint.h>
#include <stdlib.h>
#include <driver/framebuffer.h>

/* [TODO] Implement double buffering (for cursor and reading the buffer) */

static uint16_t width = 0;
static uint16_t height = 0;
static uint32_t pitch = 0;
static uint16_t bpp = 0;
static uint32_t *fb = NULL;	/* It is uint32_t because we are in 
				   RGB 32-bit mode */

void init_framebuffer(struct fb_info *fb_info) {
	if (fb_info != NULL) {
		fb = fb_info->address;
		width = fb_info->width;
		height = fb_info->height;
		pitch = fb_info->pitch;
		bpp = fb_info->bpp;
	}
}

void fb_putpixel(uint32_t color, uint16_t x, uint16_t y) {
	if (x >= width || y >= height) {
		return;
	}
	uint64_t pos = x + (y * width);
	fb[pos] = color;
}

uint16_t fb_get_width(void) {
	return width;
}

uint16_t fb_get_height(void) {
	return height;
}

uint32_t fb_get_pitch(void) {
	return pitch;
}

uint32_t *fb_get_buffer(void) {
	return fb;
}
