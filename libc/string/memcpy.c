#include "string.h"

// Derived from code in https://gitlab.com/sortie/meaty-skeleton

void *memcpy(void *restrict dst, const void *restrict src, size_t size) {
    unsigned char *dst_ptr = (unsigned char *)dst;
    const unsigned char *src_ptr = (const unsigned char *)src;
    for (size_t i = 0; i < size; ++i) {
        dst_ptr[i] = src_ptr[i];
    }
    return dst;
}

