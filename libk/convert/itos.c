#include <convert.h>
#include <stddef.h>

static size_t write_int(int number, char* buffer, size_t index, size_t size){
	size_t written = 0;
	size_t i = index;
	int rev = revint(number);
	while(rev > 0 && i < size){
		buffer[i] = itoc(rev%10);
		rev /= 10;
		i++;
		written++;
	}
	buffer[i] = '\0';

	return written;
}

size_t itos(int number, char* buffer, size_t size){
	size_t i = 0;
	size_t written = 0;
	if(size > 0){
		if(number < 0){
			buffer[i] = '-';
			number = -number;
			i++;
			written = write_int(number, buffer, i, size);
			written++;
		}else{
			written = write_int(number, buffer, i, size);	
		}
	}
	return written;
}
