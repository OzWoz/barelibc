// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <wctype.h>
#include <string.h>

int iswctype(wint_t wc, wctype_t desc)
{
	switch (desc) {
	case wctype_alnum:
		return iswalnum(wc);
	case wctype_alpha:
		return iswalpha(wc);
	case wctype_blank:
		return iswblank(wc);
	case wctype_cntrl:
		return iswcntrl(wc);
	case wctype_digit:
		return iswdigit(wc);
	case wctype_graph:
		return iswgraph(wc);
	case wctype_lower:
		return iswlower(wc);
	case wctype_print:
		return iswprint(wc);
	case wctype_punct:
		return iswpunct(wc);
	case wctype_space:
		return iswspace(wc);
	case wctype_upper:
		return iswupper(wc);
	case wctype_xdigit:
		return iswxdigit(wc);
	default:
		return 0;
	}
}

///
