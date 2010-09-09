// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#ifndef ____STDIO_INNER_H
#define ____STDIO_INNER_H

#ifndef __STDDEF_H
#include <stddef.h>
#endif

#ifndef __STDIO_H
#include <stdio.h>
#endif

#ifndef __STDARG_H
#include <stdarg.h>
#endif

#define PFORMAT_TO_FILE     1
#define PFORMAT_NOLIMIT     2

#ifdef __cplusplus
extern "C" {
#endif

unsigned int __pformat(int mode, void *buf, unsigned int sz, const char *fmt, va_list ap);
int __fputc_nolock(int c, FILE *f);

#ifdef __cplusplus
}
#endif

#endif //____STDIO_INNER_H

///

