#include <stdlib.h>
#include <stdint.h>
#include <libk/stdio.h>
#include <io/console.h>
#include <io/ps2_keyboard.h>
#include <libk/ctype.h>
#include <libk/ascii.h>

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

char *gets(char *buffer, uint32_t count) {
	uint32_t index = 0;
	uint8_t ch = 0;

	while ((ch = getchar()) != '\n' && index < count - 1) {
		if (isprint(ch) || isspace(ch) || ch == '\t') {
			buffer[index] = ch;
			index++;
			putchar(ch);
			continue;
		}

		if (ch == ASCII_BS) {
			if (index > 0) {
				index--;
				console_backspace(buffer[index]);
				buffer[index] = ASCII_BS;
			}
		}
	}
	
	buffer[index] = '\0';

	return buffer;
}
