// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#ifndef __WCTYPE_H
#define __WCTYPE_H

#ifndef __STDDEF_H
#include <stddef.h>
#endif

#ifndef __WCHAR_H
#include <wchar.h>
#endif

#ifndef __CTYPE_H
#include <ctype.h>
#endif

typedef enum {
	wctype_none = 0,
	wctype_alnum,
	wctype_alpha,
	wctype_blank,
	wctype_cntrl,
	wctype_digit,
	wctype_graph,
	wctype_lower,
	wctype_print,
	wctype_punct,
	wctype_space,
	wctype_upper,
	wctype_xdigit,
} wctype_t;

typedef enum {
	wctrans_none = 0,
	wctrans_tolower,
	wctrans_toupper,
} wctrans_t;

#define iswblank isblank
#define iswspace isspace
#define iswdigit isdigit
#define iswupper isupper
#define iswlower islower
#define iswcntrl iscntrl
#define iswprint isprint
#define iswalpha isalpha
#define iswalnum isalnum
#define iswgraph isgraph
#define iswpunct ispunct
#define iswxdigit isxdigit
#define towlower tolower
#define towupper toupper

#ifdef __cplusplus
extern "C" {
#endif

#define wctype BLC_PREFIX(wctype)
#define iswctype BLC_PREFIX(iswctype)
#define wctrans BLC_PREFIX(wctrans)
#define towctrans BLC_PREFIX(towctrans)

wctype_t wctype(const char *prop);
int iswctype(wint_t wc, wctype_t desc);
wctrans_t wctrans(const char *prop);
wint_t towctrans(wint_t wc, wctrans_t desc);

#ifdef __cplusplus
}
#endif

#endif //__WCTYPE_H

///
