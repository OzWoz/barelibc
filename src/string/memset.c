// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <string.h>

void *memset(void * restrict dst0, int c0, size_t length)
{
	unsigned char *dst = dst0;
	for (; length > 0; length--) *dst++ = (unsigned char)c0;
	return dst0;
}

///
