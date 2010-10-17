// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdlib.h>

int BLC_PREFIX(atoi)(char * restrict s)
{
	return (int)strtol(s, NULL, 10);
}