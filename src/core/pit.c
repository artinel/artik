#include <core/pit.h>
#include <stdint.h>
#include <utils/iox.h>
#include <ports.h>
#include <core/int/isr.h>
#include <core/int/irq.h>
#include <libk/stdio.h>
#include <stdbool.h>

static uint32_t tick = 0;
static uint32_t count = 0;
static void (*pit_callback)(void) = 0;
static bool is_run = false;

void pit_set_count(uint32_t c) {
	count = c;
	tick = 0;
}

uint32_t pit_get_count(void) {
	return count;
}


void pit_handler(struct registers *regs) {
	if (regs->int_no != 32) {
		return;
	}

	if (is_run == false) {
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

void pit_start(void) {
	is_run = true;
}

void pit_stop(void) {
	is_run = false;
}
