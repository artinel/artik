/**
* \file libk/convert/itos.c
* \brief Convert an integer to string
* \author Artinel <artinel@proton.me>
* \version 0.0.1
* \date 2025-03-07
* \copyright GNU Public License V3
*/

#include <convert.h>
#include <stddef.h>


/**
 * Write an integer to buffer.
 *
 * \param number The number that will be written to buffer
 * \param buffer The buffer that the number will be written on
 * \param index Start index of the buffer
 * \param size Size of the bufferr
 *
 * \return write_int returns the number of bytes written to buffer
 *
 * \sa revint itoc
 */

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

/**
 * Convert a number to string and write it to buffer.
 *
 * \param number The number that will be converted to string
 * \param buffer The buffer that the converted number will be written on
 * \param size Size of the buffer
 *
 * \return itos returns the number of bytes written to buffer
 * 
 * \sa write_int
 */

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
