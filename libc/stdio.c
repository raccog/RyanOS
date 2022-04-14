#include "stdio.h"

static Output output;

void set_output(WriteString write_string) {
    output.write_string = write_string;
}

int putc(char c) {
    char str[2];
    str[0] = c;
    str[1] = '\0';
    return output.write_string((const char *)str);
}

int puts(const char *str) {
    return output.write_string(str);
}

int printf(const char *format, ...) {
    return -1;
}
