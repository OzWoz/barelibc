// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <inttypes.h>

intmax_t BLC_PREFIX(imaxabs)(intmax_t val)
{
	return val < 0 ? -val : val;
}

///
