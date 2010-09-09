// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdlib.h>
#include <string.h>

static inline void reverse(char *s)
{
	int i, j;

	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		char c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void itoa(int n, char *s, int b)
{
	int i = 0;

	if (n < 0) {
		n = -n;
        *(s++) = '-';
	}
	do {
		int r = n % b;
		s[i++] = r < 10 ? r + '0' : r + 'a';
	} while ((n /= b) > 0);
	s[i] = 0;
	reverse(s);
}

///
