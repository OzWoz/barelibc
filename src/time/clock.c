// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <time.h>
#include <__os.h>

clock_t clock(void)
{
	int c;
	__os_get_timecounter(&c);
	return (clock_t)c;
}