// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdlib.h>
#include <string.h>
#include <smp.h>

static volatile char *__heap_ptr = 0;
static volatile size_t __heap_size = 0;
static volatile size_t __heap_used = 0;
static volatile mutex_t __mem_mutex = 0;

void __init_alloc(volatile void *ptr, size_t size)
{
	__heap_ptr = (volatile char *)ptr;
	__heap_size = size;
	__heap_used = 0;
	__mem_mutex = 0;
}

void free(void *ptr)
{

}

void *malloc(size_t size)
{
	void *ptr;
	mutex_lock(&__mem_mutex);
	if (__heap_size >= __heap_used + size) {
		ptr = (void *)(__heap_ptr+__heap_used);
		__heap_used += size;
	} else {
		ptr = NULL;
	}
	mutex_unlock(&__mem_mutex);
	return ptr;
}

void *realloc(void *ptr, size_t size)
{
	void *newptr;
	if (size == 0) {
		return NULL;
	}
	newptr = malloc(size);
	if (newptr) memcpy(newptr, ptr, size);
	free(ptr);
	return newptr;
}

void *calloc(size_t nmemb, size_t size)
{
	size_t s = nmemb*size;
	void *ptr = malloc(s);
	if (ptr) memset(ptr, 0, s);
	return ptr;
}

///
