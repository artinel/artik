#include <convert.h>

char xtoc(int c){
	char* chars = "0123456789ABCDEF";
	if(c >= 0 && c <= 15){
		return chars[c];
	}else{
		return (char) 0;
	}
}
