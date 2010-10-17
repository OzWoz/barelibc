// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdlib.h>

size_t BLC_PREFIX(mbstowcs)(wchar_t * restrict pwcs, const char * restrict s, size_t n)
{
	int ret;
	for (ret = 0; n; ret++, n--) {
		if ((*pwcs++ = *s++) == 0) break;
	}
	return ret;
}

///
