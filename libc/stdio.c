#include "stdio.h"

static Output output = {
    .write_string = NULL
};

void set_output(WriteString write_string) {
    output.write_string = write_string;
}

int putc(char c) {
    char str[2];
    if (output.write_string == NULL) {
        return -1;
    }
    str[0] = c;
    str[1] = '\0';
    return output.write_string((const char *)str);
}

int puts(const char *str) {
    if (output.write_string == NULL) {
        return -1;
    }
    return output.write_string(str);
}

int printf(const char *format, ...) {
    return -1;
}
