#pragma once

void init_malloc(void *page_start, size_t page_size);

void free(void *ptr);
void *malloc(size_t size);
