#ifndef _LIBK_CONVERT_H
#define _LIBK_CONVERT_H

#include <stddef.h>

char itoc(int c);
size_t itos(int number, char* buffer, size_t size);
int revint(int number);
size_t xtos(int number, char* buffer, size_t size);
char xtoc(int c);

#endif
