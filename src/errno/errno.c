// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <errno.h>
#include <smp.h>

int __errno[MAX_THREAD_NUM];

char __errstr[][256] = {
"EDOM",
"EILSEQ",
"ERANGE",
};


///
