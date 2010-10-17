// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdlib.h>

long BLC_PREFIX(labs)(long num)
{
	return num < 0 ? -num : num;
}

///
