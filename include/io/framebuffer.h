#ifndef __FRAMEBUFFER_H_
#define __FRAMEBUFFER_H_

#include <stdint.h>

struct fb_info {
	void *address;		/* A pointer to framebuffer */
	uint16_t width;		/* Screen width */
	uint16_t height;	/* Screen height */
	uint32_t pitch;		/* How many bytes to skip in order 
				   to go down one pixel */
	uint16_t bpp;		/* Bytes per pixel */
};

void init_framebuffer(struct fb_info *fb_info);
void fb_putpixel(uint32_t color, uint16_t x, uint16_t y);

#endif
