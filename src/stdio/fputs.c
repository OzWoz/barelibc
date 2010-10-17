// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdio.h>
#include "__stdio_inner.h"

int BLC_PREFIX(fputs)(const char *s, FILE *f)
{
	int i;
	mutex_lock(&f->mutex);
	for (i = 0; s[i]; i++) {
		if (__fputc_nolock(s[i], f) == EOF) {
			return EOF;
		}
	}
	mutex_unlock(&f->mutex);
	return i;
}

///
