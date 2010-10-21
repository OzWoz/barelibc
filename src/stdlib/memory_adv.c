// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <smp.h>

//#define MEMORY_DEBUG

#ifdef MEMORY_DEBUG
	#define FORMATPTR(p) ((p) ? PTRDIFF((p), __first) : 0)
#endif

#define SL_MAX 100000

typedef volatile struct header_s header_t;

struct header_s {
	unsigned marker;
	unsigned type;
	size_t size;
	header_t *prev;
	header_t *next;
};

static __inline int cmp(const void *dummy, const unsigned *a, const unsigned *b)
{
	header_t *pa = *(header_t **)a;
	header_t *pb = *(header_t **)b;
	if (pa->size > pb->size) return 1;
	if (pa->size < pb->size) return -1;
	if (pa->prev > pb->prev) return 1;
	if (pa->prev < pb->prev) return -1;
	return 0;
}

static __inline void *fakerealloc(const void *dummy, const void *ptr, unsigned size)
{
	return NULL;
}

#define SL_PREFIX(x) sl_##x
#define SL_ATTR static __inline
#define SL_STATICATTR static __inline
#define SL_HASBLINK 0
#define SL_KEYSIZE (sizeof(size_t)/sizeof(unsigned))
#define SL_VALUESIZE 0
#define SL_RAND urand
#define SL_CMP cmp
#define SL_KEYCPY(key1,key2,dummy) *(header_t **)key1 = *(header_t **)key2
#define SL_VALUECPY(x,y,z) ((void)0)
#define SL_REALLOC fakerealloc
#define SL_PRINT

#include "sl_h.h"
#include "sl_c.h"

#define _MARK_ 0x4b52414dU
#define _FREE_ 0x45455246U
#define _USED_ 0x44455355U

static header_t *__first = NULL;
static mutex_t __mem_mutex = 0;
static sl_t __sl;

void __init_alloc(volatile void *ptr, size_t size)
{
	unsigned sls;

	assert(ptr != NULL);

	sls = (sl_size(SL_MAX)+3)&~3;

	assert(size >= sls+1024);
	
	__first = (header_t *)((volatile unsigned *)ptr+sls);
	__first->marker = _MARK_;
	__first->type = _FREE_;
	__first->size = size - sls*sizeof(unsigned) - sizeof(header_t);
	__first->prev = NULL;
	__first->next = NULL;
	sl_init(&__sl, (unsigned *)ptr, sls, NULL);
	sl_insert(&__sl, (unsigned *)&__first, NULL, NULL);
}

static void __free_nolock(void *ptr)
{
	header_t *head;
	if (ptr == NULL) {
		return;
	}
	head = ((header_t *)ptr)-1;
	assert(head->marker == _MARK_);
	assert(head->type == _USED_);
	if (head->next) {
		assert(head->next->marker == _MARK_);
		assert(head->next->type == _FREE_ || head->next->type == _USED_);
	}
	if (head->prev) {
		assert(head->prev->marker == _MARK_);
		assert(head->prev->type == _FREE_ || head->prev->type == _USED_);
	}

	if (head->next != NULL && head->next->type == _FREE_) {
		unsigned k;
		head->size += head->next->size + sizeof(header_t);
		k = sl_search(&__sl, (unsigned *)&(head->next));
		assert(k != UNOTFOUND);
		sl_delete(&__sl, k, NULL);
		head->next->marker = 0;
		head->next->type = 0;
		head->next = head->next->next;
		if (head->next) {
			head->next->prev = head;
		}
	}

	if (head->prev == NULL || head->prev->type == _USED_) {
		head->type = _FREE_;
		sl_insert(&__sl, (unsigned *)&head, NULL, NULL);
	} else {
		unsigned k;
		header_t *prev = head->prev;
		k = sl_search(&__sl, (unsigned *)&prev);
		assert(k != UNOTFOUND);
		sl_delete(&__sl, k, NULL);
		prev->size += head->size + sizeof(header_t);
		head->marker = 0;
		head->type = 0;
		prev->next = head->next;
		if (prev->next) {
			prev->next->prev = prev;
		}
		sl_insert(&__sl, (unsigned *)&prev, NULL, NULL);
	}
}

void BLC_PREFIX(free)(void *ptr)
{
	mutex_lock(&__mem_mutex);
	__free_nolock(ptr);
	mutex_unlock(&__mem_mutex);
#ifdef MEMORY_DEBUG
	printf("free: %p\n", FORMATPTR(ptr));
#endif
}

static void *__malloc_nolock(size_t size)
{
	unsigned k;
	header_t *gap;
	header_t key, *pkey;
	size = (size+15)&~15;
	key.size = size;
	key.prev = NULL;
	pkey = &key;
	k = sl_nsearch(&__sl, (unsigned *)&pkey, NULL);
	if (k == UNOTFOUND) {
		return NULL;
	}
	gap = *(header_t **)sl_getkey(&__sl, k);
	sl_delete(&__sl, k, NULL);
	assert(gap->marker == _MARK_);
	assert(gap->type == _FREE_);
	gap->type = _USED_;
	if (gap->size >= size+sizeof(header_t)+16) {
		header_t *ins = (header_t *)(((char *)(gap+1))+size);
		ins->next = gap->next;
		if (ins->next) ins->next->prev = ins;
		ins->prev = gap;
		gap->next = ins;
		ins->size = gap->size-size-sizeof(header_t);
		gap->size = size;
		ins->marker = _MARK_;
		ins->type = _FREE_;
		sl_insert(&__sl, (unsigned *)&ins, NULL, NULL);
	}
	return (void *)(gap+1);
}

void *BLC_PREFIX(malloc)(size_t size)
{
	void *ret;
	mutex_lock(&__mem_mutex);
	ret = __malloc_nolock(size);
	mutex_unlock(&__mem_mutex);
#ifdef MEMORY_DEBUG
	printf("malloc: %p => %p\n", size, FORMATPTR(ret));
#endif
	return ret;
}

static void *__realloc_nolock(void *ptr, size_t size)
{
	unsigned k;
	size_t gapsize, oldsize;
	header_t *gap, *head;
	void *newptr;
	if (ptr == NULL) {
		return __malloc_nolock(size);
	}
	if (size == 0) {
		__free_nolock(ptr);
		return NULL;
	}
	size = (size+15)&~15;
	head = ((header_t *)ptr)-1;
	assert(head->marker == _MARK_);
	assert(head->type == _USED_);
	oldsize = head->size;
	if (size <= oldsize && size+sizeof(header_t)+16 >= oldsize) {
		return ptr;
	}
	gapsize = oldsize;
	gap = head;
	if (head->next && head->next->type == _FREE_) {
		gapsize += head->next->size + sizeof(header_t);
	}
	if (head->prev && head->prev->type == _FREE_) {
		gapsize += head->prev->size + sizeof(header_t);
		gap = head->prev;
	}
	if (gapsize >= size) {
		newptr = (void *)(gap+1);
		__free_nolock(ptr);
		if (gap != head) {
			memmove(newptr, ptr, oldsize < size ? oldsize : size);
		}
		k = sl_search(&__sl, (unsigned *)&gap);
		assert(k != UNOTFOUND);
		sl_delete(&__sl, k, NULL);
		gap->type = _USED_;
		if (gap->size >= size+sizeof(header_t)+16) {
			header_t *ins = (header_t *)(((char *)(gap+1))+size);
			ins->next = gap->next;
			if (ins->next) ins->next->prev = ins;
			ins->prev = gap;
			gap->next = ins;
			ins->size = gap->size-size-sizeof(header_t);
			gap->size = size;
			ins->marker = _MARK_;
			ins->type = _FREE_;
			sl_insert(&__sl, (unsigned *)&ins, NULL, NULL);	
		}
	} else {
		newptr = __malloc_nolock(size);
		if (newptr == NULL) {
			return NULL;
		}
		memcpy(newptr, ptr, oldsize < size ? oldsize : size);
		__free_nolock(ptr);	
	}
	return newptr;
}

void *BLC_PREFIX(realloc)(void *ptr, size_t size)
{
	void *ret;
	mutex_lock(&__mem_mutex);
	ret = __realloc_nolock(ptr, size);
	mutex_unlock(&__mem_mutex);
#ifdef MEMORY_DEBUG
	printf("realloc: %p %p => %p\n", FORMATPTR(ptr), size, FORMATPTR(ret));
	sl_print(&__sl);
#endif
	return ret;
}

void *BLC_PREFIX(calloc)(size_t nmemb, size_t size)
{
	size_t s = nmemb*size;
	void *ptr = malloc(s);
	if (ptr) memset(ptr, 0, s);
	return ptr;
}

///
