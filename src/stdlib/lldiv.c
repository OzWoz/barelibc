// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdlib.h>

lldiv_t BLC_PREFIX(lldiv)(long long numer, long long denom)
{
	lldiv_t ret;
	ret.quot = numer/denom;
	ret.rem = numer%denom;
	if (numer >= 0 && ret.rem < 0) {
		ret.quot++;
		ret.rem -= denom;
	}
	return ret;
}

///
