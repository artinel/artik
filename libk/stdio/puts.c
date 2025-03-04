#include <stdio.h>
#include <stddef.h>
#include <string.h>

size_t puts(const char* str){
	size_t written = 0;
	size_t len = strlen(str);

	for(size_t i = 0; i < len; i++){
		putchar(str[i]);
		written++;
	}
	
	return written;
}
