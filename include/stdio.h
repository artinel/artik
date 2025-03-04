#ifndef _LIBK_STDIO_H
#define _LIBK_STDIO_H

#include <stddef.h>

#define EOF (-1)

int putchar(int);
size_t puts(const char* str);
size_t printk(const char* str, ...);

#endif
