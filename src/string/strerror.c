// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <string.h>
#include <errno.h>

char *BLC_PREFIX(strerror)(int n)
{
	if (n < 0 || n >= EMAXERROR) return NULL;
	return __errstr[n];
}

///
