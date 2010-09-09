// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#ifndef __CTYPE_H
#define __CTYPE_H

#ifndef __STDDEF_H
#include <stddef.h>
#endif

#define isblank(c) ((c) == ' ' || (c) == '\t')
#define isspace(c) ((c) == ' ' || (c) == '\t' || (c) == '\r' || (c) == '\n' || (c) == '\v' || (c) == '\f')
#define isdigit(c) ((c) >= '0' && (c) <= '9')
#define isupper(c) ((c) >= 'A' && (c) <= 'Z')
#define islower(c) ((c) >= 'a' && (c) <= 'z')
#define iscntrl(c) ((c) <= '\x1F' || (c) == '\x7F')
#define isprint(c) ((c) >= '\x20' && (c) <= '\x7F')
#define isalpha(c) (isupper(c) || islower(c))
#define isalnum(c) (isalpha(c) || isdigit(c))
#define isgraph(c) (isprint(c) && !isspace(c))
#define ispunct(c) (isgraph(c) && !isalnum(c))
#define isxdigit(c) (isdigit(c) || ((c) >= 'a' && (c) <= 'f') || ((c) >= 'A' && (c) <= 'F'))
#define tolower(c) (isupper(c) ? (c)-'A'+'a' : (c))
#define toupper(c) (islower(c) ? (c)-'a'+'A' : (c))

#endif //__CTYPE_H

///
