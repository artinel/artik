#include <libk/string.h>
#include <libk/stdint.h>

void *memset(void *dest, int c, size_t count) {
	for (size_t i = 0; i < count; i++) {
		((char *)dest)[i] = c;
	}

	return dest;
}
