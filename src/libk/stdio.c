#include <stdlib.h>
#include <stdint.h>
#include <libk/stdio.h>
#include <io/console.h>
#include <io/ps2_keyboard.h>
#include <libk/ctype.h>
#include <libk/ascii.h>
#include <stdarg.h>
#include <libk/stdlib.h>

#define BUF_SIZE	20

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

	while ((ch = getchar()) != '\n') {
		if (isprint(ch) || isspace(ch) || ch == '\t') {
			if (index == count - 1) {
				break;
			}

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

int printf(const char *str, ...) {
	va_list v_list;
	va_start(v_list, str);
	uint32_t index = 0;
	char c = 0;
	while ((c = str[index]) != 0) {
		if (c == '%') {
			char p_holder = str[index + 1];
			if (p_holder == 's') {
				puts(va_arg(v_list, char*));
				index += 2;
				continue;
			}
			
			if (p_holder == 'd') {
				char buffer[BUF_SIZE];
				sitoa(va_arg(v_list, int), buffer, 
						sizeof(buffer), BASE_10);
				puts(buffer);
				index += 2;
				continue;
			}

			if (p_holder == 'x') {
				char buffer[BUF_SIZE];
				sitoa(va_arg(v_list, long), buffer, 
						sizeof(buffer), BASE_16);
				puts(buffer);
				index += 2;
				continue;
			}

			if (p_holder == 'c') {
				putchar(va_arg(v_list, int));
				index += 2;
				continue;
			}
			
			if (p_holder == 'u') {
				char u_holder = str[index + 2];
				if (u_holder == 'd' || u_holder == 'l') {
					char buffer[BUF_SIZE];
					itoa(va_arg(v_list, unsigned long), 
							buffer, 
							sizeof(buffer),
							BASE_10);
					puts(buffer);
					index += 3;
					continue;
				}

				if (u_holder == 'x') {
					char buffer[BUF_SIZE];
					itoa(va_arg(v_list, unsigned long), 
							buffer, 
							sizeof(buffer),
							BASE_16);
					puts(buffer);
					index += 3;
					continue;
				}

				if (u_holder == 'c') {
					putchar(va_arg(v_list, int));
					index += 3;
					continue;
				}

				putchar('%');
				putchar(p_holder);
				putchar(u_holder);
				index += 3;
				continue;
			}

			putchar('%');
			putchar(p_holder);
			index += 2;
			continue;

		} else {
			putchar(c);
			index++;
		}
	}
	return index;
}
