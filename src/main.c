#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>
#include <io/framebuffer.h>
#include <io/console.h>
#include <libk/stdio.h>
#include <kernel/idt.h>
#include <kernel/isr.h>
#include <limits.h>
#include <logo.h>

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
	

	/* Initialize the console */
	init_console();
	console_set_foreground(0x1E88E5);

	struct console *console = console_get_self();

	uint32_t logo_len = 0;

	while (logo[logo_len] != '\n') {
		logo_len++;
	}

	if (logo_len > console->max_col) {
		goto logo_too_big;
	}

	logo_len = console->max_col - logo_len; 
	logo_len /= 2;
	
	uint32_t index = 0;
	while (logo[index] != 0) {
		if (console->col == 0) {
			console->col = logo_len;
		}
		putchar(logo[index]);
		index++;
	}

logo_too_big:

	console_set_foreground(0xFFFFFF);
	puts("Framebuffer Initialized\n");
	puts("Console Initialized\n");

	init_idt();
	puts("IDT Initialized\n");

	init_isr();
	__asm volatile ("sti");
	puts("ISRs Initialized\n");

	puts("Kernel is ready!!!\n");
	
	/* We are done. just halt the kernel*/
	halt();
}
