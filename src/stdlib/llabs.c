// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdlib.h>

long long BLC_PREFIX(llabs)(long long num)
{
	return num < 0 ? -num : num;
}

///
