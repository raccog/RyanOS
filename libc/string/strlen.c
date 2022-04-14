#include "string.h"

// Derived from code in https://gitlab.com/sortie/meaty-skeleton

size_t strlen(const char *str) {
    size_t len = 0;
    while (str[len]) {
        ++len;
    }
    return len;
}
