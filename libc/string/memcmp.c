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

