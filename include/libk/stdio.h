#ifndef __LIBK_STDIO_H_
#define __LIBK_STDIO_H_

#include <stdint.h>

#define EOF -1

int putchar(int c);
int puts(const char *str);
int getchar(void);
char *gets(char *buffer, uint32_t count);
int printf(const char *str, ...);

#endif
