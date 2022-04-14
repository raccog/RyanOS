#include "stdio.h"

#include <stdarg.h>

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

static int print_ptr(u64 value) {
    puts("0x");

    for (int i = 15; i >= 0; --i) {
        u8 hex_val = (value >> (i * 4)) & 0xf;
        if (hex_val < 0xa) {
            if (putc('9' - (9 - hex_val)))
                return -1;
        } else {
            if (putc('f' - (0xf - hex_val)))
                return -1;
        }
    }

    return 0;
}

static int print_hex(u32 value) {
    puts("0x");

    for (int i = 7; i >= 0; --i) {
        u8 hex_val = (value >> (i * 4)) & 0xf;
        if (hex_val < 0xa) {
            if (putc('9' - (9 - hex_val)))
                return -1;
        } else {
            if (putc('f' - (0xf - hex_val)))
                return -1;
        }
    }

    return 0;
}

static int print_int(int value) {
    size_t digits = 1;
    int divisor;

    if (value < 0) {
        if (putc('-'))
            return -1;
        value *= -1;
    }

    // count number of digits
    for (divisor = 10; divisor <= value; divisor *= 10) {
        ++digits;
    }
    divisor /= 10;

    while (digits > 0) {
        u8 digit = (value / divisor) % 10;
        if (putc('9' - (9 - digit)))
            return -1;
        --digits;
        divisor /= 10;
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
                    if (print_ptr((u64)va_arg(args, long)))
                        return -1;
                case 'i':
                case 'd':
                    if (print_int(va_arg(args, int)))
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
