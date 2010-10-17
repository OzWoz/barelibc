// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#ifndef __LOCALE_H
#define __LOCALE_H

#ifndef __STDDEF_H
#include <stddef.h>
#endif

enum {
	LC_ALL,
	LC_COLLATE,
	LC_CTYPE,
	LC_MONETARY,
	LC_NUMERIC,
	LC_TIME
};

struct lconv {
	char *decimal_point; // "."
	char *thousands_sep; // ""
	char *grouping; // ""
	char *mon_decimal_point; // ""
	char *mon_thousands_sep; // ""
	char *mon_grouping; // ""
	char *positive_sign; // ""
	char *negative_sign; // ""
	char *currency_symbol; // ""
	char frac_digits; // CHAR_MAX
	char p_cs_precedes; // CHAR_MAX
	char n_cs_precedes; // CHAR_MAX
	char p_sep_by_space; // CHAR_MAX
	char n_sep_by_space; // CHAR_MAX
	char p_sign_posn; // CHAR_MAX
	char n_sign_posn; // CHAR_MAX
	char *int_curr_symbol; // ""
	char int_frac_digits; // CHAR_MAX
	char int_p_cs_precedes; // CHAR_MAX
	char int_n_cs_precedes; // CHAR_MAX
	char int_p_sep_by_space; // CHAR_MAX
	char int_n_sep_by_space; // CHAR_MAX
	char int_p_sign_posn; // CHAR_MAX
	char int_n_sign_posn; // CHAR_MAX
};

#ifdef __cplusplus
extern "C" {
#endif

#define setlocale BLC_PREFIX(setlocale)
#define localeconv BLC_PREFIX(localeconv)

char *setlocale(int category, const char *locale);
struct lconv *localeconv(void);

#ifdef __cplusplus
}
#endif

#endif //__LOCALE_H

///
