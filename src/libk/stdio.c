#include <stdlib.h>
#include <libk/stdio.h>
#include <io/console.h>
#include <io/ps2_keyboard.h>

int putchar(int c) {
	if (console_putchar(c) >= 0) {
		return c;
	}
	return EOF;
}

int puts(const char *str) {

	if (str == NULL) {
		return EOF;
	}

	int index = 0;
	while (str[index] != 0) {
		if (putchar(str[index]) == EOF) {
			return EOF;
		}
		index++;
	}

	return index;
}

static uint8_t getchar_c = 0;

static void getchar_callback(uint8_t c) {
	getchar_c = c;
}

int getchar(void) {
	ps2_keyboard_get_char(getchar_callback);
	return (int)getchar_c;
}
