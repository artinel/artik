/**
* \file libk/convert/xtoc.c
* \brief Convert hexadecimal to character
* \author Artinel <artinel@proton.me>
* \version 0.0.1
* \date 2025-03-07
* \copyright GNU Public License V3
*/

#include <convert.h>

/**
* Convert hexadecimal to character(6 -> '6' , 10 -> 'A' and etc...).
*
* \param c The hexadecimal value that will be converted to character
*
* \return xtoc returns the converted character
*/

char xtoc(int c){
	char* chars = "0123456789ABCDEF";
	if(c >= 0 && c <= 15){
		return chars[c];
	}else{
		return (char) 0;
	}
}
