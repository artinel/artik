#include <convert.h>

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
