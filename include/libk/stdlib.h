#ifndef __LIBK_STDLIB_H_
#define __LIBK_STDLIB_H_

#include <stdint.h>

enum base_type{
	BASE_2,
	BASE_10,
	BASE_16
};

void itoa(long num, char *buffer, uint32_t buf_size, enum base_type type);

#endif
