// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdlib.h>

int BLC_PREFIX(abs)(int num)
{
	return num < 0 ? -num : num;
}

///
