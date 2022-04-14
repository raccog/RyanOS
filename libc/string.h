#ifndef STRING_H
#define STRING_H

// Derived from code in https://gitlab.com/sortie/meaty-skeleton

#ifdef __cplusplus
extern "C" {
#endif

int memcmp(const void *a, const void *b, size_t size);
void *memcpy(void *__restrict dst, const void *__restrict src, size_t size);
void *memmove(void *dst, const void *src, size_t size);
void *memset(void *dst, int value, size_t size);
size_t strlen(const char *str);

#ifdef __cplusplus
}
#endif

#endif
