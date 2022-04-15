# Possible Malloc Implementations

Considerations of a malloc and free implementation are described here.

C-like pseudo-code will be included as needed.

## No Free

This possible implementation keeps track of a single pointer as the start of free memory and moves it forward on every malloc call.

On initialization, the saved pointer is set to the start of currently allocated pages.

```c
void *heap = ALLOCATED_PAGE_START;
```

This implementation does the following on a malloc call:

1. Return currently saved pointer
2. Move pointer forward by the caller requested size

```c
void *malloc(size_t n) {
	void *ptr = heap;
	heap += n;
	return ptr;
}
```

Since the heap pointer is only moved forward and all returned pointers are not kept track of, memory in this implementation cannot be freed.

```c
void free(void *ptr) {
	return;
}
```

Pros:

* Very fast
* Very simple
* Very low overhead (just a single pointer)

Cons:

* Memory is extremely limited because it cannot be freed

## Other Implementations to Research

* Boundary tag
* Two power