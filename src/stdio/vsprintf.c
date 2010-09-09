// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdio.h>
#include "__stdio_inner.h"

int vsprintf(char *buf, const char *format, va_list args)
{
	return __pformat(PFORMAT_NOLIMIT, buf, 0, format, args);
}

///
