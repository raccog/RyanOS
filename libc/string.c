#include "string.h"

// Derived from code in https://gitlab.com/sortie/meaty-skeleton

int memcmp(const void *a, const void *b, size_t size) {
    const unsigned char *a_ptr = (const unsigned char *)a;
    const unsigned char *b_ptr = (const unsigned char *)b;
    for (size_t i = 0; i < size; ++i) {
        unsigned char cmp_a = a_ptr[i];
        unsigned char cmp_b = b_ptr[i];
        if (cmp_a < cmp_b) {
            return -1;
        } else if (cmp_a > cmp_b) {
            return 1;
        }
    }
    return 0;
}

void *memcpy(void *restrict dst, const void *restrict src, size_t size) {
    unsigned char *dst_ptr = (unsigned char *)dst;
    const unsigned char *src_ptr = (const unsigned char *)src;
    for (size_t i = 0; i < size; ++i) {
        dst_ptr[i] = src_ptr[i];
    }
    return dst;
}

void *memmove(void *dst, const void *src, size_t size) {
    unsigned char *dst_ptr = (unsigned char *)dst;
    const unsigned char *src_ptr = (const unsigned char *)src;
    if (dst_ptr < src_ptr) {
        for (size_t i = 0; i < size; ++i) {
            dst_ptr[i] = src_ptr[i];
        }
    } else {
        for (size_t i = size; i != 0; --i) {
            dst_ptr[i - 1] = src_ptr[i - 1];
        }
    }
    return dst;
}

void *memset(void *dst, int value, size_t size) {
    int *dst_ptr = (int *)dst;
    for (size_t i = 0; i < size; ++i) {
        *dst_ptr = value;
    }

    return dst;
}

size_t strlen(const char *str) {
    size_t len = 0;
    while (str[len]) {
        ++len;
    }
    return len;
}
