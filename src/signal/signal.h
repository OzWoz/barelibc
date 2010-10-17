// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#ifndef __SIGNAL_H
#define __SIGNAL_H

#ifndef __STDDEF_H
#include <stddef.h>
#endif

#define SIG_DFL 0
#define SIG_ERR 1
#define SIG_IGN 2

typedef enum {
	SIGABRT,
	SIGFPE,
	SIGILL,
	SIGINT,
	SIGSEGV,
	SIGTERM,
} __signal_t;

typedef volatile char sig_atomic_t;

#define signal(x, y) ((void)0)

#ifdef __cplusplus
extern "C" {
#endif

#define raise BLC_PREFIX(raise)

int raise(int sig);

#ifdef __cplusplus
}
#endif


#endif //__SIGNAL_H

///
