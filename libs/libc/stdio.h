#pragma once

#define EOF (-1)

typedef int (*WriteString)(const char *str);

typedef struct {
	WriteString write_string;
} Output;

int putc(char c);
int puts(const char *str);
int printf(const char *format, ...);

void set_output(WriteString write_string);
