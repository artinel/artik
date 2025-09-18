#include <libk/stdlib.h>
#include <stdint.h>
#include <libk/ctype.h>
#include <kernel/pit.h>
#include <stdbool.h>

static bool is_sleep = false;

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
	
	if (num == 0) {
		buffer[0] = '0';
		buffer[1] = 0;
		return;
	}
	
	const char *x_digits = "0123456789ABCDEF";
	uint8_t count = digit_count(num, type);
	uint8_t index = count - 1;
	uint8_t term = count;
	uint8_t divisor = 10;

	if (type == BASE_16) {
		divisor = 16;
	}

	if (num < 0) {
		if (buf_size < (uint32_t)count + 2) {
			buffer[0] = 0;
			return;
		}
		
		buffer[0] = '-';
		num = -(num);
		index++;
		term++;
	}
	
	if (buf_size < (uint32_t)count + 1) {
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
	
	if (num == 0) {
		buffer[0] = '0';
		buffer[1] = 0;
		return;
	}
	
	const char *x_digits = "0123456789ABCDEF";
	uint8_t count = udigit_count(num, type);
	uint8_t index = count - 1;
	uint8_t term = count;
	uint8_t divisor = 10;

	if (type == BASE_16) {
		divisor = 16;
	}

	if (buf_size < (uint32_t)count + 1) {
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

uint64_t uatoi(const char *str) {
	uint64_t res = 0;
	const char *p_str = str;
	while (*p_str != 0) {
		if (isdigit(*p_str)) {
			res *= 10;
			res += (*p_str - '0');
		}
		p_str++;
	}

	return res;
}

static void sleep_callback(void) {
	is_sleep = false;
}

void sleep(uint16_t sec) {
	/* Save the current pit count so we can restore it later */
	uint32_t count_tmp = pit_get_count();

	pit_set_count(sec * PIT_COUNT_PER_SEC);
	pit_set_callback(sleep_callback);
	pit_start();

	is_sleep = true;

	while (is_sleep == true) {}

	pit_stop();
	pit_remove_callback();
	/* Restore the previous pit count */
	pit_set_count(count_tmp);
}
