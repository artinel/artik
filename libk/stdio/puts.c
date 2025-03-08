/**
* \file libk/stdio/puts.c
* \brief Print a string on the screen
* \author Artinel <artinel@proton.me>
* \version 0.0.1
* \date 2025-03-08
* \copyright GNU Public License V3
*/

#include <stdio.h>
#include <stddef.h>
#include <string.h>

/**
* Print a string on the screen.
*
* \param str The string that will be printed on the screen
*
* \return puts returns the number of bytes printed on the screen
*
* \sa strlen putchar
*/

size_t puts(const char* str){
	size_t written = 0;
	size_t len = strlen(str);

	for(size_t i = 0; i < len; i++){
		putchar(str[i]);
		written++;
	}
	
	return written;
}
