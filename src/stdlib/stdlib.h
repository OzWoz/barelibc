// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#ifndef __STDLIB_H
#define __STDLIB_H

#ifndef __STDDEF_H
#include <stddef.h>
#endif

#ifndef __STRING_H
#include <string.h>
#endif

#ifndef __SETJMP_H
#include <setjmp.h>
#endif

#ifndef __SIGNAL_H
#include <signal.h>
#endif

typedef struct {
	int quot;
	int rem;
} div_t;

typedef struct {
	long quot;
	long rem;
} ldiv_t;

typedef struct {
	long long quot;
	long long rem;
} lldiv_t;

typedef enum {
	__ATEXIT_TYPE_NOARG,
	__ATEXIT_TYPE_ARG,
} __atexit_type_t;

typedef struct __atexit_s __atexit_t;

struct __atexit_s {
	__atexit_type_t type;
	union {
		void (*noarg)(void);
		void (*arg)(void *);
	} fnc;
	void *arg;
	__atexit_t *next;
};

#ifdef __cplusplus
extern "C" {
#endif

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define NORMAL_EXIT_CODE 123456

extern void *__dso_handle;

int atexit(void (*func)(void));
int atexit_arg(void (*func)(void *), void *arg);
int __cxa_atexit(void (*func)(void *), void *arg, void *dso_handle);

void _Exit(int ret);
void exit(int ret);
#define abort() raise(SIGABRT)

#define RAND_MAX ((1U<<31)-1)
void srand(unsigned seed);
unsigned urand(void);
int rand(void);

void itoa(int n, char *s, int b);

void __init_alloc(volatile void *ptr, size_t size);
void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void *calloc(size_t nmemb, size_t size);

#define MB_CUR_MAX 1
int mbtowc(wchar_t * restrict pwc, const char * restrict s, size_t n);
int wctomb(char * restrict s, wchar_t wc);
#define mblen(s, n) mbtowc(NULL, s, n)
size_t mbstowcs(wchar_t * restrict pwcs, const char * restrict s, size_t n);
#define wcstombs mbstowcs

long strtol(const char * restrict nptr, char ** restrict endptr, int base);
long long strtoll(const char * restrict nptr, char ** restrict endptr, int base);
unsigned long strtoul(const char * restrict nptr, char ** restrict endptr, int base);
unsigned long long strtoull(const char * restrict nptr, char ** restrict endptr, int base);
int atoi(char * restrict s);
long atol(char * restrict s);
long long atoll(char * restrict s);

char *getenv(const char *name);
int system(const char *str);

int abs(int num);
long labs(long num);
long long llabs(long long num);

div_t div(int numer, int denom);
ldiv_t ldiv(long numer, long denom);
lldiv_t lldiv(long long numer, long long denom);

void qsort(void *a, size_t n, size_t es, int (*cmp)(const void *, const void *));
void qsort_arg(void *a, size_t n, size_t es, int (*cmp)(void *, const void *, const void *), void *arg);
void *bsearch(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
void *bsearch_arg(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(void *, const void *, const void *), void *arg);

#ifdef __cplusplus
}
#endif

#endif //__STDLIB_H

///
