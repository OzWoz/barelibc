// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdlib.h>

long long atoll(char * restrict s)
{
	return strtoll(s, NULL, 10);
}