// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdio.h>
#include <__os.h>
#include "__stdio_inner.h"

int __fputc_nolock(int c, FILE *f)
{
	if (f->handle == 0) {
		switch (c) {
		case '\n':
			__os_print_newline();
			break;
		case '\r':
			break;
		default:
			__os_print_char(c);
		}
		return c;
	} else {
		//file
		return EOF;
	}
}

int BLC_PREFIX(fputc)(int c, FILE *f)
{
	int ret;
	mutex_lock(&f->mutex);
	ret = __fputc_nolock(c, f);
	mutex_unlock(&f->mutex);
	return ret;
}

///
