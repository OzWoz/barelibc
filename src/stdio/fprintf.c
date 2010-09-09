// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdio.h>
#include "__stdio_inner.h"

int fprintf(FILE *f, const char *format, ...)
{
	int ret;
	va_list args;
	va_start(args, format);
	ret = vfprintf(f, format, args);
	va_end(args);
	return ret;
}

///
