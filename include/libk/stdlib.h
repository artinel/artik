#ifndef __LIBK_STDLIB_H_
#define __LIBK_STDLIB_H_

#include <stdint.h>

enum base_type{
	BASE_2,
	BASE_10,
	BASE_16
};

void sitoa(int64_t num, char *buffer, uint32_t buf_size, enum base_type type);
void itoa(uint64_t num, char *buffer, uint32_t buf_size, enum base_type type);
uint64_t uatoi(const char *str);
void sleep(uint16_t sec);
void *kmalloc(uint32_t size);
uint8_t kfree(void *address);

#endif
