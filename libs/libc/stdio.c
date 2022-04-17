#include "stdio.h"

#include <stdarg.h>

static Output output = {
	.write_string = NULL
};

void set_output(WriteString write_string) {
	output.write_string = write_string;
}

int putc(char c) {
	const char str[] = {c, '\0'};
	if (output.write_string == NULL) {
		return -1;
	}
	return output.write_string(str);
}

int puts(const char *str) {
	if (output.write_string == NULL) {
		return -1;
	}
	return output.write_string(str);
}

static int print_ptr(u64 value) {
	char buffer[19];
	size_t buf_index = 2;

	buffer[0] = '0';
	buffer[1] = 'x';
	buffer[18] = '\0';

	for (int i = 15; i >= 0; --i) {
		u8 hex_val = (value >> (i * 4)) & 0xf;
		if (hex_val < 0xa) {
			buffer[buf_index] = '9' - (9 - hex_val);
		} else {
			buffer[buf_index] = 'f' - (0xf - hex_val);
		}
		++buf_index;
	}

	if (puts(buffer)) {
		return -1;
	}

	return 0;
}

static int print_hex(u32 value) {
	char buffer[11];
	size_t buf_index = 2;

	buffer[0] = '0';
	buffer[1] = 'x';
	buffer[10] = '\0';

	for (int i = 7; i >= 0; --i) {
		u8 hex_val = (value >> (i * 4)) & 0xf;
		if (hex_val < 0xa) {
			buffer[buf_index] = '9' - (9 - hex_val);
		} else {
			buffer[buf_index] = 'f' - (0xf - hex_val);
		}
		++buf_index;
	}

	if (puts(buffer)) {
		return -1;
	}

	return 0;
}

static int print_uint(u32 value) {
	char buffer[11];
	buffer[10] = '\0';

	// Print 0 and return if value is 0
	if (value == 0) {
		if (putc('0')) {
			return -1;
		}
		return 0;
	}

	// Start at the end of the buffer, while leaving a null terminator
	// at the end.
	size_t buf_index = 9;
	const int DIVISOR = 10;
	do {
		buffer[buf_index] = ('0' + (value % DIVISOR));
		value /= DIVISOR;
		--buf_index;
	} while (value > 0);
	++buf_index;	// Ensure index points to first digit

	// Print number
	if (puts(&buffer[buf_index])) {
		return -1;
	}

	return 0;
}

static int print_int(int value) {
	char buffer[12];
	bool is_negative = true;

	buffer[11] = '\0';

	// Print 0 and return if value is 0
	if (value == 0) {
		if (putc('0')) {
			return -1;
		}
		return 0;
	}

	// Swap positive value to negative
	//
	// Negative values are used for calculations because 
	// swapping the smallest negative number to be positive
	// causes an integer overflow.
	if (value > 0) {
		is_negative = false;
		value *= -1;
	}

	// From this point, value will always be a negative integer.
	//
	// Start at the end of the buffer, while leaving a null terminator
	// at the end.
	size_t buf_index = 10;
	const int DIVISOR = 10;
	do {
		buffer[buf_index] = ('0' - (value % DIVISOR));
		value /= DIVISOR;
		--buf_index;
	} while (value < 0);

	// Add negative sign if value was originally negative
	if (is_negative) {
		buffer[buf_index] = '-';
	} else {
		++buf_index;	// Ensure index points to first digit
	}

	// Print number
	if (puts(&buffer[buf_index])) {
		return -1;
	}

	return 0;
}

// TODO: Buffer string
int printf(const char *format, ...) {
	va_list args;
	char c;

	va_start(args, format);

	while ((c = *format++) != '\0') {
		if (c == '%') {
			c = *format++;
			switch (c) {
				case 'c':
					if (putc((char)va_arg(args, int)))
						return -1;
					break;
				case 's':
					if (puts(va_arg(args, const char *)))
						return -1;
					break;
				case 'x':
					if (print_hex((u32)va_arg(args, int)))
						return -1;
					break;
				case 'p':
					if (print_ptr((u64)va_arg(args, u64)))
						return -1;
					break;
				case 'i':
				case 'd':
					if (print_int(va_arg(args, int)))
						return -1;
					break;
				case 'u':
					if (print_uint(va_arg(args, u32)))
						return -1;
					break;
				default:
					if (putc(c))
						return -1;
			}
		} else if (c == '\n') {
			if (puts("\r\n"))
				return -1;
		} else {
			if (putc(c))
				return -1;
		}
	}

	return 0;
}
