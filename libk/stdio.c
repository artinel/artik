#include <libk/stdio.h>
#include <libk/stdlib.h>
#include <video/tty.h>

int putc(char c) {
	if (tty_putchar(c) == RET_SUCCESS) {
		return c;
	}
	return EOF;
}

int puts(const char *str) {
	int index = 0;

	while (str[index] != 0) {
		if (putc(str[index]) == EOF) {
			return EOF;
		}
		index++;
	}

	return index;
}
