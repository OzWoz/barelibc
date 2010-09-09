// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <inttypes.h>

intdiv_t imaxdiv(intmax_t numer, intmax_t denom)
{
	intdiv_t ret;
	ret.quot = numer/denom;
	ret.rem = numer%denom;
	return ret;
}