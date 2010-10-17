// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#ifndef __STRING_H
#define __STRING_H

#ifndef __STDDEF_H
#include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define memcmp BLC_PREFIX(memcmp)
#define memmove BLC_PREFIX(memmove)
#define memset BLC_PREFIX(memset)
#define memchr BLC_PREFIX(memchr)
#define strerror BLC_PREFIX(strerror)
#define strcmp BLC_PREFIX(strcmp)
#define strncmp BLC_PREFIX(strncmp)
#define strcpy BLC_PREFIX(strcpy)
#define strlen BLC_PREFIX(strlen)
#define strcat BLC_PREFIX(strcat)
#define strncat BLC_PREFIX(strncat)
#define strchr BLC_PREFIX(strchr)
#define strstr BLC_PREFIX(strstr)
#define strcspn BLC_PREFIX(strcspn)
#define strpbrk BLC_PREFIX(strpbrk)
#define strrchr BLC_PREFIX(strrchr)
#define strspn BLC_PREFIX(strspn)
#define strtok BLC_PREFIX(strtok)

int memcmp(const void *s1, const void *s2, size_t n);
void *memmove(void *s1, const void *s2, size_t n);
#define memcpy memmove
void *memset(void * restrict s, int c, size_t n);
void *memchr(const void * restrict s, int c, size_t n);

char *strerror(int n);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
char *strcpy(char * restrict s1, const char * restrict s2);
char *strncpy(char * restrict dst, const char * restrict src, size_t n);
size_t strlen(const char * restrict s);
char *strcat(char * restrict s, const char * restrict append);
char *strncat(char * restrict dst, const char * restrict src, size_t n);
char *strchr(const char *p, int ch);
char *strstr(const char *s, const char *find);
#define strcoll strcmp
#define strxfrm(s1, s2, n) strlen(s1)
size_t strcspn(const char *s, const char *charset);
char *strpbrk(const char *s1, const char *s2);
char *strrchr(const char * restrict p, int ch);
size_t strspn(const char *s, const char *charset);
char *strtok(char *s, const char *delim);


#ifdef __cplusplus
}
#endif

#endif //__STRING_H

///
