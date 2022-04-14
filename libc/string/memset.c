#include "string.h"

// Derived from code in https://gitlab.com/sortie/meaty-skeleton

void *memset(void *dst, int value, size_t size) {
    int *dst_ptr = (int *)dst;
    for (size_t i = 0; i < size; ++i) {
        *dst_ptr = value;
    }

    return dst;
}
