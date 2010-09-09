// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#ifndef __STDIO_H
#define __STDIO_H

#ifndef __STDDEF_H
#include <stddef.h>
#endif

#ifndef __STDARG_H
#include <stdarg.h>
#endif

#ifndef __SMP_H
#include <smp.h>
#endif

typedef struct {
	mutex_t mutex;
	int handle;
} FILE;

extern FILE __stdin;
extern FILE __stdout;
extern FILE __stderr;

#define EOF (-1)

#define stdin (&__stdin)
#define stdout (&__stdout)
#define stderr (&__stderr)

#ifdef __cplusplus
extern "C" {
#endif

int fputc(int c, FILE *f);
#define putc fputc
#define putchar(c) fputc((c), stdout)

int fputs(const char *s, FILE *f);
#define puts(s) fputs((s), stdout)

int fprintf(FILE *f, const char *format, ...);
#define printf(...) fprintf(stdout, __VA_ARGS__)
int snprintf(char *buf, int maxlen, const char *format, ...);
int sprintf(char *buf, const char *format, ...);
int vfprintf(FILE *f, const char *format, va_list args);
#define vprintf(f, a) vfprintf(stdout, (f), (a))
int vsnprintf(char *buf, int maxlen, const char *format, va_list args);
int vsprintf(char *buf, const char *format, va_list args);

#ifdef __cplusplus
}
#endif

#endif //__STDIO_H

///
