// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <locale.h>
#include <limits.h>
#include <string.h>

static struct lconv __locale = {".", "", "", "", "", "", "", "", "",
CHAR_MAX, CHAR_MAX, CHAR_MAX, CHAR_MAX, CHAR_MAX, CHAR_MAX, CHAR_MAX, "",
CHAR_MAX, CHAR_MAX, CHAR_MAX, CHAR_MAX, CHAR_MAX, CHAR_MAX, CHAR_MAX};

static char *__locale_name_ = "";
static char *__locale_name_C = "C";


char *BLC_PREFIX(setlocale)(int category, const char *locale)
{
	if (locale) {
		if (locale[0] == 0) {
			__locale_name_[0] = 0;
			return __locale_name_;
		}
		if (locale[0] == 'C' && locale[1] == 0) {
			__locale_name_C[0] = 'C';
			__locale_name_C[1] = 0;
			return __locale_name_C;
		}
		return NULL;
	}
	return __locale_name_C;
}

struct lconv *BLC_PREFIX(localeconv)(void)
{
	__locale.decimal_point[0] = '.';
	__locale.decimal_point[1] = 0;
	__locale.thousands_sep[0] = 0;
	__locale.grouping[0] = 0;
	__locale.mon_decimal_point[0] = 0;
	__locale.mon_thousands_sep[0] = 0;
	__locale.mon_grouping[0] = 0;
	__locale.positive_sign[0] = 0;
	__locale.negative_sign[0] = 0;
	__locale.currency_symbol[0] = 0;
	__locale.frac_digits = CHAR_MAX;
	__locale.p_cs_precedes = CHAR_MAX;
	__locale.n_cs_precedes = CHAR_MAX;
	__locale.p_sep_by_space = CHAR_MAX;
	__locale.n_sep_by_space = CHAR_MAX;
	__locale.p_sign_posn = CHAR_MAX;
	__locale.n_sign_posn = CHAR_MAX;
	__locale.int_curr_symbol[0] = 0;
	__locale.int_frac_digits = CHAR_MAX;
	__locale.int_p_cs_precedes = CHAR_MAX;
	__locale.int_n_cs_precedes = CHAR_MAX;
	__locale.int_p_sep_by_space = CHAR_MAX;
	__locale.int_n_sep_by_space = CHAR_MAX;
	__locale.int_p_sign_posn = CHAR_MAX;
	__locale.int_n_sign_posn = CHAR_MAX;
	return &__locale;
}

///
