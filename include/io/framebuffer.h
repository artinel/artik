#ifndef __FRAMEBUFFER_H_
#define __FRAMEBUFFER_H_

#include <stdint.h>

struct fb_info {
	void *address;
	uint16_t width;
	uint16_t height;
	uint32_t pitch;
	uint16_t bpp;
};

void init_framebuffer(struct fb_info *fb_info);
void fb_putpixel(uint32_t color, uint16_t x, uint16_t y);

#endif
