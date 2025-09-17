#include <libk/stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <io/scancodes.h>
#include <io/ps2_keyboard.h>
#include <io/ports.h>
#include <kernel/irq.h>
#include <io/iox.h>

#define ESC	0x1B
#define BS	0x08
#define HT	0x09	
#define LF	0x0A
#define SP	0x20

static uint8_t ascii_lower[] = {
	0x0,  ESC,  '1',  '2',
	'3',  '4',  '5',  '6',
	'7',  '8',  '9',  '0',
	'-',  '=',   BS,   HT,
	'q',  'w',  'e',  'r',
	't',  'y',  'u',  'i',
	'o',  'p',  '[',  ']',
	 LF,  0x0,  'a',  's',
	'd',  'f',  'g',  'h',
	'j',  'k',  'l',  ';',
	'\'', '`',  0x0,  '\\',
	'z',  'x',  'c',  'v',
	'b',  'n',  'm',  ',',
	'.',  '/',  0x0,  '*',
	0x0,   SP,  0x0,  0x0,
	0x0,  0x0,  0x0,  0x0,
	0x0,  0x0,  0x0,  0x0,
	0x0,  0x0,  0x0,  '7',
	'8',  '9',  '-',  '4',
	'5',  '6',  '+',  '1',
	'2',  '3',  '0',  '.',
	0x0,  0x0,  0x0,  0x0,
	0x0,  0x0,  0x0,  0x0
};

static uint8_t ascii_upper[] = {
	0x0,  ESC,  '!',  '@',
	'#',  '$',  '%',  '^',
	'&',  '*',  '(',  ')',
	'_',  '+',   BS,   HT,
	'Q',  'W',  'E',  'R',
	'T',  'Y',  'U',  'I',
	'O',  'P',  '{',  '}',
	 LF,  0x0,  'A',  'S',
	'D',  'F',  'G',  'H',
	'J',  'K',  'L',  ':',
	'"',  '~',  0x0,  '|',
	'Z',  'X',  'C',  'V',
	'B',  'N',  'M',  '<',
	'>',  '?',  0x0,  '*',
	0x0,   SP,  0x0,  0x0,
	0x0,  0x0,  0x0,  0x0,
	0x0,  0x0,  0x0,  0x0,
	0x0,  0x0,  0x0,  '7',
	'8',  '9',  '-',  '4',
	'5',  '6',  '+',  '1',
	'2',  '3',  '0',  '.',
	0x0,  0x0,  0x0,  0x0,
	0x0,  0x0,  0x0,  0x0
};

static bool shift = false;
static bool extended = false;
static bool raw_mode = false;
static bool char_mode = false;
static void (*raw_callback)(uint8_t code, bool is_extended);
static void (*char_callback)(uint8_t ch);

void ps2_keyboard_handler(struct registers *r) {
	outb(PS2_KB_STATUS, 0);
	uint8_t scancode = inb(PS2_KB_DATA);

	if (raw_mode == true) {
		if (scancode == KE_MASK) {
			extended = true;
			return;
		}
		raw_callback(scancode, extended);
		raw_callback = 0;
		raw_mode = false;
		extended = false;
		return;
	}

	if (char_mode == false) {
		puts("CHAR MOD IS FALSE\n");
		return;
	}

	if (scancode == KE_MASK) {
		extended = true;
		return;
	}

	if (extended == true) {
		extended = false;
		return;
	}

	if (scancode == K_LSHIFT_P || scancode == K_RSHIFT_P) {
		shift = true;
	} else if (scancode == K_LSHIFT_R || scancode == K_RSHIFT_R) {
		shift = false;
	}

	uint8_t ch = 0;

	if (shift == true) {
		ch = ascii_upper[scancode];
	} else {
		ch = ascii_lower[scancode];
	}

	if (ch > 0 && scancode < 0x81) {
		char_callback(ch);
		char_callback = 0;
		char_mode = false;
	}
}

/* Installs the keyboard handler into IRQ1 */
void init_ps2_keyboard() {
	irq_install_handler(1, ps2_keyboard_handler);
}

void ps2_keyboard_get_raw(void (*callback)(uint8_t, bool)) {
	raw_mode = true;
	raw_callback = callback;
	while (raw_mode == true) {
		//TODO put a timer here(for waiting)
	}
}

void ps2_keyboard_get_char(void (*callback)(uint8_t)) {
	char_mode = true;
	char_callback = callback;
	while (char_mode == true) {
		//TODO put a timer here(for waiting)
	}
}
