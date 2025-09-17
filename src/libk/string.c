#include <libk/string.h>
#include <stddef.h>
#include <stdint.h>

void *memmove(void *dest, const void *src, size_t n) {
     	uint8_t *pdest = (uint8_t *)dest;
	const uint8_t *psrc = (const uint8_t *)src;

	if (src > dest) {
		for (size_t i = 0; i < n; i++) {
		pdest[i] = psrc[i];
		}
	} else if (src < dest) {
		for (size_t i = n; i > 0; i--) {
		pdest[i-1] = psrc[i-1];
		}
	}

	return dest;
}

void *memset(void *dest, int c, size_t count) {
	uint8_t *ptr = (uint8_t *) dest;
	
	for (size_t i = 0; i < count; i++) {
		ptr[i] = (uint8_t) c;
	}

	return dest;
}

int strcmp(const char *s1, const char *s2) {
	while (*s1 == *s2 && *s1 != 0 && *s2 != 0) {
		s1++;
		s2++;
	}

	if (*s1 == *s2) {
		return 0;
	} else if (*s1 > *s2) {
		return 1;
	} else {
		return -1;
	}
}
