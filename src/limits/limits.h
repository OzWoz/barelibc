// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#ifndef __LIMITS_H
#define __LIMITS_H

#ifndef __STDDEF_H
#include <stddef.h>
#endif

#define CHAR_BIT 8
#define SHRT_BIT 16
#define INT_BIT 32
#define LONG_BIT 64
#define LLONG_BIT 64

#define SCHAR_MAX ((char)0x7f)
#define SHRT_MAX ((short)0x7fff)
#define INT_MAX 0x7fffffff
#define LLONG_MAX 0x7fffffffffffffffLL

#define SCHAR_MIN ((char)(-SCHAR_MAX - 1))
#define SHRT_MIN ((short)(-SHRT_MAX - 1))
#define INT_MIN (-INT_MAX - 1)
#define LLONG_MIN (-LLONG_MAX - 1LL)

#define UCHAR_MAX ((unsigned char)0xffU)
#define USHRT_MAX ((unsigned short)0xffffU)
#define UINT_MAX 0xffffffffU
#define ULLONG_MAX 0xffffffffffffffffULL

#ifdef __os_windows
	#define LONG_MIN INT_MIN
	#define LONG_MAX INT_MAX
	#define ULONG_MAX UINT_MAX
#else
	#define LONG_MIN LLONG_MIN
	#define LONG_MAX LLONG_MAX
	#define ULONG_MAX ULLONG_MAX
#endif


#define CHAR_MIN SCHAR_MIN
#define CHAR_MAX SCHAR_MAX

#endif //__LIMITS_H

///
