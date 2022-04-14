#include "string.h"

void *memset(void *ptr, int value, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        *(int *)ptr = value;
    }

    return ptr;
}
