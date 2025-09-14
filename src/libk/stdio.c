#include <stdlib.h>
#include <libk/stdio.h>
#include <io/console.h>

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
