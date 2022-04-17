#include "stdlib.h"

static void *heap;
static void *heap_end;

void free(void *ptr) {
	return;
}

void init_malloc(void *page_start, size_t page_size) {
	// TODO: Ensure heap is aligned
	heap = page_start;
	heap_end = heap + page_size;
}

void *malloc(size_t size) { 
	// Ensure there is enough free memory
	if (heap + size >= heap_end) {
		return NULL;
	}

	// Get pointer to return to caller
	void *ptr = heap;

	// Update heap
	heap += size;

	// Ensure heap is aligned by 8 bytes
	u8 align = (uptr)heap % 8;
	if (align != 0) {
		heap += 8 - align;
	}

	return ptr;
}
