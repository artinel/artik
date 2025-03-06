/**
* \file libk/convert/itoc.c
* \brief Convert integer to character
* \author Artinel <artinel@proton.me>
* \version 0.0.1
* \date 2025-03-06
* \copyright GNU Public License V3
*/

#include <convert.h>

/**
* Convert number(integer) to the corresponding character.
* itoc returns the converted character.
* Example : 0 = '0' , 1 = '1' , 2 = '2' and etc.
*
* \param c The integer that will be converted to character (0 >= c <= 9)
* \bug Does not check if the integer is between 0 and 9 (0 >= c <= 9)
* \todo Check if the integer is between 0 and 9 (0 >= c <= 9)
*/

char itoc(int c){
	return (char) c + '0';
}
