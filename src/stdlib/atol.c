// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdlib.h>

long atol(char * restrict s)
{
	return strtol(s, NULL, 10);
}