// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#ifndef __TIME_H
#define __TIME_H

#ifndef __STDDEF_H
#include <stddef.h>
#endif

#ifndef ____OS_H
#include <__os.h> 
#endif

//CLOCKS_PER_SEC comes from __os.h

typedef unsigned long long time_t;
typedef unsigned long long clock_t;

struct tm {
	int tm_sec; // seconds after the minute — [0, 60]
	int tm_min; // minutes after the hour — [0, 59]
	int tm_hour; // hours since midnight — [0, 23]
	int tm_mday; // day of the month — [1, 31]
	int tm_mon; // months since January — [0, 11]
	int tm_year; // years since 1900
	int tm_wday; // days since Sunday — [0, 6]
	int tm_yday; // days since January 1 — [0, 365]
	int tm_isdst; // Daylight Saving Time flag
};

#ifdef __cplusplus
extern "C" {
#endif

#define clock BLC_PREFIX(clock)
#define time BLC_PREFIX(time)

clock_t clock(void);
time_t time(time_t *ptr);

#define difftime(t1, t0) ((double)t1-(double)t0)

#ifdef __cplusplus
}
#endif

#endif //__TIME_H

///
