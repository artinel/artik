/**
* \file libk/stdio/printk.c
* \brief Print formatted text on the screen
* \author Artinel <artinel@proton.me>
* \version 0.0.1
* \date 2025-03-08
* \copyright GNU Public License V3
*/

#include <stdio.h>
#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <convert.h>

/**
* Print formatted text on the screen.
*
* \param str The output format string
* \param ... The arguments for the format string
*
* \return printk returns the number of bytes printed on the screen
*
* \sa strlen puts itos xtos putchar
*/

size_t printk(const char* str, ...){
        va_list args;
        va_start(args, str);
	size_t written = 0;
	size_t len = strlen(str);

	for(size_t i = 0; i < len; i++){
		if(str[i] == '%'){
			if(str[i+1] == 's'){
				written += puts(va_arg(args, char*));	
			}else if(str[i+1] == 'd'){
				char buffer[20];
				itos(va_arg(args, int) , buffer, sizeof(buffer));
				written += puts(buffer);
			}else if(str[i+1] == 'x'){
				char buffer[20];
				xtos(va_arg(args, int), buffer, sizeof(buffer));
				written += puts(buffer);
			}
			i++;
		}else{
			putchar(str[i]);
			written++;
		}
	}

        return written;
}
