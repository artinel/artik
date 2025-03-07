/**
* \file libk/convert/xtos.c
* \brief Convert hexadecimal to string
* \author Artinel <artinel@proton.me>
* \version 0.0.1
* \date 2025-03-07
* \copyright GNU Public License V3
*/


#include <convert.h>
#include <stddef.h>

/**
* Convert hexadecimal to string and write it to buffer.
*
* \param number The hexadecimal number that will be converted to string
* \param buffer The buffer that the converted number will be written on
* \param size Size of the buffer
*
* \return xtos returns the number of bytes written to buffer
*
* \sa xtoc
*/

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
