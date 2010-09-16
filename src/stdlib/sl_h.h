// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file


//need SL_PREFIX, SL_ATTR

#ifndef UERROR
#define UNOTFOUND ((unsigned)-1)
#define UERROR ((unsigned)-2)
#define UNONE ((unsigned)-3)
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#ifndef UINT64
#ifdef __BORLANDC__
typedef unsigned __int64 UINT64;
#else
typedef unsigned long long UINT64;
#endif
#endif

#define SL_MAXLEVEL 23 /* >log(2*10^9) */

typedef struct SL_PREFIX(s) {
	unsigned *links[SL_MAXLEVEL];
	void *callbackptr;
	unsigned allocated[SL_MAXLEVEL];
	unsigned empty[SL_MAXLEVEL];
	unsigned itemsize[SL_MAXLEVEL];
	unsigned usedlevel;
	unsigned isstatic;
	unsigned num;
} SL_PREFIX(t);

#ifdef __cplusplus
extern "C" {
#endif
	SL_ATTR unsigned SL_PREFIX(head)(void);
	SL_ATTR unsigned SL_PREFIX(size)(unsigned num);
	SL_ATTR void SL_PREFIX(clear)(SL_PREFIX(t) *pl);
	SL_ATTR unsigned SL_PREFIX(init)(SL_PREFIX(t) *pl, unsigned *buf, unsigned size, void *reallocptr);
	SL_ATTR void SL_PREFIX(exit)(SL_PREFIX(t) *pl);
	SL_ATTR unsigned SL_PREFIX(insert)(SL_PREFIX(t) *pl, unsigned *newkey, unsigned *newvalue, unsigned *found);
	SL_ATTR unsigned SL_PREFIX(search)(SL_PREFIX(t) *pl, void *searchkey);
	SL_ATTR unsigned SL_PREFIX(psearch)(SL_PREFIX(t) *pl, void *searchkey, unsigned *found);
	SL_ATTR unsigned SL_PREFIX(nsearch)(SL_PREFIX(t) *pl, void *searchkey, unsigned *found);
	SL_ATTR void SL_PREFIX(delete)(SL_PREFIX(t) *pl, unsigned k, unsigned *found);
	SL_ATTR unsigned SL_PREFIX(next)(SL_PREFIX(t) *pl, unsigned k);
	SL_ATTR unsigned SL_PREFIX(prev)(SL_PREFIX(t) *pl, unsigned k);
	SL_ATTR unsigned *SL_PREFIX(getkey)(SL_PREFIX(t) *pl, unsigned k);
	SL_ATTR unsigned *SL_PREFIX(getvalue)(SL_PREFIX(t) *pl, unsigned k);
	SL_ATTR unsigned SL_PREFIX(num)(SL_PREFIX(t) *pl);
	#ifdef SL_PRINT
	SL_ATTR void SL_PREFIX(print)(SL_PREFIX(t) *pl);
	#endif
#ifdef __cplusplus
}
#endif

///
