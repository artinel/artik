#include <convert.h>
#include <stddef.h>

size_t xtos(int number, char* buffer, size_t size){
	size_t i = 0;
	size_t written = 0;
	int temp_count = number;
	while(temp_count > 0){
		temp_count /= 16;
		i++;
	}

	buffer[i] = '\0';

	while(number > 0 && i <= size){
		i--;
		buffer[i] = xtoc(number%16);
		number /= 16;
		written++;
	}

	return written;
}
