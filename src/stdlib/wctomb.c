// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdlib.h>

int BLC_PREFIX(wctomb)(char * restrict s, wchar_t wc)
{
	if (s == NULL) return 0;
	*s = wc;
	return 1;
}

///
