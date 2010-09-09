// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#ifndef __ERRNO_H
#define __ERRNO_H

#ifndef __STDDEF_H
#include <stddef.h>
#endif

#ifndef __SMP_H
#include <smp.h>
#endif

extern int __errno[MAX_THREAD_NUM];

#define errno (__errno[thread_current_id()])

#define EDOM 0
#define EILSEQ 1
#define ERANGE 2
#define EINVAL 3

#define EMAXERROR 4

extern char __errstr[][256];

#endif //__ERRNO_H

///
