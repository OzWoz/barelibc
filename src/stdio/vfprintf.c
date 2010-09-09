// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdio.h>
#include "__stdio_inner.h"

int vfprintf(FILE *f, const char *format, va_list args)
{
	int ret;
	mutex_lock(&f->mutex);
	ret = __pformat(PFORMAT_TO_FILE | PFORMAT_NOLIMIT, f, 0, format, args);
	mutex_unlock(&f->mutex);
	return ret;
}

///
