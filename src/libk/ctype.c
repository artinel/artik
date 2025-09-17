#include <libk/ctype.h>
#include <libk/ascii.h>

int islower(int c) {
	if (c >= 'a' && c <= 'z') {
		return c;
	}

	return 0;
}

int isupper(int c) {
	if (c >= 'A' && c <= 'Z') {
		return c;
	}

	return 0;
}

int isalpha(int c) {
	return islower(c) || isupper(c);
}

int isblank(int c) {
	if (c == ASCII_SP || c == '\t') {
		return c;
	}

	return 0;
}

int isdigit(int c) {
	if (c >= '0' && c <= '9') {
		return c;
	}

	return 0;
}

int isspace(int c) {
	switch(c) {
		case ASCII_SP:
		case '\f':
		case '\n':
		case '\r':
		case '\t':
		case '\v':
			return c;
		default:
			return 0;
	}
}

int isalnum(int c) {
	return isalpha(c) || isdigit(c);
}

int isascii(int c) {
	if (c >= 0 && c <= 127) {
		return c;
	}

	return 0;
}

int isprint(int c) {
	if (c >= ASCII_SP && c <= ASCII_TILDE) {
		return c;
	}
	
	return 0;
}

int ispunct(int c) {
	if (isprint(c) == 0 || c == ASCII_SP) {
		return 0;
	}

	if (isalnum(c) == 0) {
		return c;
	}

	return 0;
}

int isgraph(int c) {
	if (isprint(c) != 0 && c != ASCII_SP) {
		return c;
	}

	return 0;
}

int iscntrl(int c) {
	if ((c >= ASCII_NULL && c <= ASCII_US) || c == ASCII_DEL) {
		return c;
	}

	return 0;
}

int isxdigit(int c) {
	if ((c >= '0' && c <= '9') || 
			(c >= 'a' && c <= 'f') || 
			(c >= 'A' && c <= 'F')) {
	
		return c;
	}

	return 0;
}
