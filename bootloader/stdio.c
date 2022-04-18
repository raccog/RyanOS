#include "stdio.h"

EfiSimpleTextOutputProtocol *console_out; 
EfiSimpleTextOutputProtocol *console_out_err; 

// Wrapper to write char to UEFI console output
int uefi_write_character(char c) {
	EfiChar16 str[] = {(EfiChar16)c, L'\0'};
	console_out->output_string(console_out, str);
	return 0;
}

// Wrapper to write string to UEFI console output
int uefi_write_string(const char *str) {
	const size_t BUF_LEN = 0x200;
	EfiChar16 buffer[BUF_LEN];
	size_t index = 0;

	// Copy string into buffer, while flushing to console when the buffer is full
	while (*str != '\0') {
		buffer[index++] = (EfiChar16)*str++;
		if (index >= BUF_LEN - 1) {
			buffer[index] = L'\0';
			index = 0;
			console_out->output_string(console_out, buffer);
		}
	}

	// Flush buffer if its not empty
	if (index > 0) {
		buffer[index] = L'\0';
		console_out->output_string(console_out, buffer);
	}

	return 0;
}

void uefi_init_stdio(EfiSystemTable *st) {
	
}
