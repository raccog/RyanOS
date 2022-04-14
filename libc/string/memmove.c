#include "string.h"

// Derived from code in https://gitlab.com/sortie/meaty-skeleton

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
