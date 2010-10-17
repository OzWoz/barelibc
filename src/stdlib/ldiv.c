// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdlib.h>

ldiv_t BLC_PREFIX(ldiv)(long numer, long denom)
{
	ldiv_t ret;
	ret.quot = numer/denom;
	ret.rem = numer%denom;
	if (numer >= 0 && ret.rem < 0) {
		ret.quot++;
		ret.rem -= denom;
	}
	return ret;
}

///
