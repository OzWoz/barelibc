// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <time.h>

time_t BLC_PREFIX(time)(time_t *ptr)
{
	time_t t = (time_t)(clock()/CLOCKS_PER_SEC);
	if (ptr) *ptr = t;
	return t;
}