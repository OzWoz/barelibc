// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <wctype.h>
#include <string.h>

wctype_t BLC_PREFIX(wctype)(const char *prop)
{
	if (!strcmp(prop, "alnum")) return wctype_alnum;
	if (!strcmp(prop, "alpha")) return wctype_alpha;
	if (!strcmp(prop, "blank")) return wctype_blank;
	if (!strcmp(prop, "cntrl")) return wctype_cntrl;
	if (!strcmp(prop, "digit")) return wctype_digit;
	if (!strcmp(prop, "graph")) return wctype_graph;
	if (!strcmp(prop, "lower")) return wctype_lower;
	if (!strcmp(prop, "print")) return wctype_print;
	if (!strcmp(prop, "punct")) return wctype_punct;
	if (!strcmp(prop, "space")) return wctype_space;
	if (!strcmp(prop, "upper")) return wctype_upper;
	if (!strcmp(prop, "xdigit")) return wctype_xdigit;
	return wctype_none;
}

///
