// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdlib.h>

int BLC_PREFIX(mbtowc)(wchar_t * restrict pwc, const char * restrict s, size_t n)
{
	if (s == NULL || n == 0) return 0;
	if (pwc != NULL) *pwc = *s;
	if (*s == 0) return 0;
	return 1;
}

///
