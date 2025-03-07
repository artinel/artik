/**
* \file libk/convert/revint.c
* \brief Reverse an integer
* \author Artinel <artinel@proton.me>
* \version 0.0.1
* \date 2025-03-07
* \copyright GNU Public License V3
*/

#include <convert.h>

/**
* Reverse an integer(456 -> 654 ane etc...).
*
* \param number The number that will be reversed
*
* \return revint returns the reversed number
*/
int revint(int number){
	if(number < 0){
		number = -number;
	}
	int res = 0;
	while(number > 0){
		res *= 10;
		res += number % 10;
		number /= 10;
	}

	if(number < 0){
		res = -res;
	}
	return res;
}
