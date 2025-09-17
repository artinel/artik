#include <libk/stdlib.h>
#include <stdint.h>

static uint8_t digit_count(int64_t num, enum base_type type) {
	
	uint8_t divisor = 10;

	if (type == BASE_16) {
		divisor = 16;
	}
	
	if (num < 0) {
		num = -(num);
	}

	if (num == 0) {
		return 1;
	}

	uint8_t count = 0;

	while (num > 0) {
		num /= divisor;
		count++;
	}

	return count;
}

static uint8_t udigit_count(uint64_t num, enum base_type type) {
	
	uint8_t divisor = 10;

	if (type == BASE_16) {
		divisor = 16;
	}
	
	if (num == 0) {
		return 1;
	}

	uint8_t count = 0;

	while (num > 0) {
		num /= divisor;
		count++;
	}

	return count;
}



void itoa(int64_t num, char *buffer, uint32_t buf_size, enum base_type type) {
	const char *x_digits = "0123456789ABCDEF";
	uint8_t count = digit_count(num, type);
	uint8_t index = count - 1;
	uint8_t term = count;
	uint8_t divisor = 10;

	if (type == BASE_16) {
		divisor = 16;
	}

	if (num < 0) {
		if (buf_size < count + 2) {
			buffer[0] = 0;
			return;
		}
		
		buffer[0] = '-';
		num = -(num);
		index++;
		term++;
	}
	
	if (buf_size < count + 1) {
		buffer[0] = 0;
		return;
	}


	while (num > 0) {
		if (type == BASE_16) {
			buffer[index] = x_digits[num % divisor];
		} else {
			buffer[index] = (num % divisor) + '0';
		}
		index--;
		num /= divisor;
	}

	buffer[term] = '\0';
}


void uitoa(uint64_t num, char *buffer, uint32_t buf_size, enum base_type type) {
	const char *x_digits = "0123456789ABCDEF";
	uint8_t count = udigit_count(num, type);
	uint8_t index = count - 1;
	uint8_t term = count;
	uint8_t divisor = 10;

	if (type == BASE_16) {
		divisor = 16;
	}

	if (buf_size < count + 1) {
		buffer[0] = 0;
		return;
	}


	while (num > 0) {
		if (type == BASE_16) {
			buffer[index] = x_digits[num % divisor];
		} else {
			buffer[index] = (num % divisor) + '0';
		}
		index--;
		num /= divisor;
	}

	buffer[term] = '\0';
}
