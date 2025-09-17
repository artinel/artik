#ifndef __LIBK_STRING_H_
#define __LIBK_STRING_H_

#include <stddef.h>

void *memmove(void *dest, const void *src, size_t n);
void *memset(void *dest, int c, size_t count);
int strcmp(const char *s1, const char *s2);

#endif
