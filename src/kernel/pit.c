#include <kernel/pit.h>
#include <stdint.h>
#include <io/iox.h>
#include <io/ports.h>
#include <kernel/isr.h>
#include <kernel/irq.h>
#include <libk/stdio.h>

static uint16_t tick = 0;
static uint16_t count = 0;
static void (*pit_callback)(void) = 0;


void pit_set_count(uint16_t c) {
	count = c;
}

uint16_t pit_get_count(void) {
	return count;
}


void pit_handler(struct registers *regs) {
	if (regs->int_no != 32) {
		return;
	}
	tick++;
	if (tick == count) {
		if (pit_callback != 0) {
			pit_callback();
		}
		tick = 0;
	}
}

void init_pit(void) {
	irq_install_handler(0, pit_handler);
	pit_set_count(PIT_COUNT_PER_SEC);
}

void pit_set_callback(void (*callback)(void)) {
	pit_callback = callback;
}

void pit_remove_callback(void) {
	pit_callback = 0;
}
