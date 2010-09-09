// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdio.h>
#include "__stdio_inner.h"

int vsnprintf(char *buf, int maxlen, const char *format, va_list args)
{
	return __pformat(0, buf, maxlen, format, args);
}

///
