// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#ifndef __WCHAR_H
#define __WCHAR_H

#ifndef __STDDEF_H
#include <stddef.h>
#endif

#ifndef __STDLIB_H
#include <stdlib.h>
#endif

#ifndef __STDINT_H
#include <stdint.h>
#endif

typedef int mbstate_t;
typedef int wint_t;

#define WEOF EOF

#define fwprintf fprintf
#define fwscanf fscanf
#define swprintf snprintf
#define swscanf sscanf
#define vfwprintf vfprintf
#define vfwscanf vfscanf
#define vswprintf vsnprintf
#define vswscanf vsscanf
#define vwprintf vprintf
#define vwscanf vscanf
#define wprintf printf
#define wscanf scanf

#define fgetwc fgetc
#define fgetws fgets
#define fputwc fputc
#define fputws fputs

#define fwide(stream, mode) (-1)

#define getwc getc
#define getwchar getchar
#define putwc putc
#define putwchar putchar
#define ungetwc ungetc

#define wcstod strtod
#define wcstof strtof
#define wcstold strtold

#define wcstol strtol
#define wcstoll strtoll
#define wcstoul strtoul
#define wcstoull strtoull

#define wcscpy strcpy
#define wcsncpy strncpy
#define wmemcpy memcpy
#define wmemmove memmove
#define wcscat strcat
#define wcsncat strncat
#define wcscmp strcmp
#define wcscoll strcoll
#define wcsncmp strncmp
#define wcsxfrm strxfrm
#define wmemcmp memcmp
#define wcschr strchr
#define wcscspn strcspn
#define wcspbrk strpbrk
#define wcsrchr strrchr
#define wcsspn strspn
#define wcsstr strstr
#define wcstok strtok
#define wmemchr memchr
#define wcslen strlen
#define wmemset memset
#define wcsftime strftime

#define btowc(c) (c)
#define wctob(c) (c)

#define mbsinit(ps) 1
#define mbrtowc(pwc, s, n, ps) mbtowc(pwc, s, n)
#define mbrlen(s, n, ps) mblen(s, n)
#define wcrtomb(s, wc, ps) wctomb(s, wc)
#define mbsrtowcs(dst, src, len, ps) mbstowcs(dst, src, len)
#define wcsrtombs(dst, src, len, ps) wcstombs(dst, src, len)

#endif //__WCHAR_H

///
