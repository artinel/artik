#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>
#include <io/framebuffer.h>

/* Set the base limine revision to 3 (might change it later) */
__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3);


__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request fb_req = {
	.id = LIMINE_FRAMEBUFFER_REQUEST,
	.revision = 0
};

/* Set the start and the end markers for limine requests(Can be placed anywhere) */
__attribute__((used, section(".limine_requests_start")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile LIMINE_REQUESTS_END_MARKER;

/* [TODO] Implement memcpy, memset, memmove and memcpy */

/* Halt the kernel */
static void halt(void) {
	while (1) {
		asm ("hlt");
	}
}


/* Kernel's main function */
void main(void) {
	/* Make sure that the bootloader understands the base version */
	if (LIMINE_BASE_REVISION_SUPPORTED == false) {
		halt();
	}

	/* Ensure we got a framebuffer */
	if (fb_req.response == NULL) {
		halt();
	}

	if (fb_req.response->framebuffer_count < 1) {
		halt();
	}

	/* Fetch the first framebuffer */
	struct limine_framebuffer *framebuffer = fb_req.response->framebuffers[0];

	/* [INFO] We assume the framebuffer is RGB with 32-bit pixels*/

	/* Initialize the framebuffer */
	struct fb_info fb_info = {
		.address = framebuffer->address,
		.width = framebuffer->width,
		.height = framebuffer->height,
		.pitch = framebuffer->pitch,
		.bpp = framebuffer->bpp
	};

	init_framebuffer(&fb_info);

	/* We are done. just halt the kernel*/
	halt();
}
