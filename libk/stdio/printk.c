#include <stdio.h>
#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <convert.h>

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
			}
			i++;
		}else{
			putchar(str[i]);
			written++;
		}
	}

        return written;
}
