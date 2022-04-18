#pragma once

#define EOF (-1)

typedef int (*WriteString)(const char *str);

typedef struct {
	WriteString stdout;
	WriteString stderr;
} Stdio;

int putc(char c);
int puts(const char *str);
int printf(const char *format, ...);

void set_stdout(WriteString write_string);
void set_stderr(WriteString write_string);
