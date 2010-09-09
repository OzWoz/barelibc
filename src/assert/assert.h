// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#ifndef __ASSERT_H
#define __ASSERT_H

#ifndef __STDDEF_H
#include <stddef.h>
#endif

#ifndef __STDLIB_H
#include <stdlib.h>
#endif

#ifndef __STDIO_H
#include <stdio.h>
#endif

#ifdef NDEBUG
	#define assert(x) ((void)0)
#else                                                                                                                           
	#define assert(x) if (!(x)) do { \
	char linestr[20]; \
	fputs(__FILE__, stderr); \
	fputs(":", stderr); \
	itoa(__LINE__, linestr, 10); \
	fputs(linestr, stderr); \
	fputs(": ", stderr); \
	fputs(__func__, stderr); \
	fputs(": Assertion '", stderr); \
	fputs(#x, stderr); \
	fputs("' failed\nAbort\n", stderr); \
	abort(); \
	} while(0)

/*
	#define assert(x) if (!(x)) do { \
	fprintf(stderr, "%s:%d: %s: Assertion '%s' failed\nAbort\n", __FILE__, __LINE__, __func__, #x); \
	abort(); \
	} while(0)
*/
#endif

#endif //__ASSERT_H

///
