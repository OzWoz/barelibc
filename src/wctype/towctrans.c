// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <wctype.h>
#include <string.h>

wint_t towctrans(wint_t wc, wctrans_t desc)
{
	switch (desc) {
	case wctrans_tolower:
		return towlower(wc);
	case wctrans_toupper:
		return towupper(wc);
	default:
		return 0;
	}
}

///
