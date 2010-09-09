// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <wctype.h>
#include <string.h>

wctrans_t wctrans(const char *prop)
{
	if (!strcmp(prop, "tolower")) return wctrans_tolower;
	if (!strcmp(prop, "toupper")) return wctrans_toupper;
	return wctrans_none;
}

///
