// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#ifndef __STDDEF_H
#define __STDDEF_H

typedef long long ptrdiff_t;
typedef unsigned long long size_t;

#ifdef __cplusplus
	#define restrict __restrict
#else
	typedef char wchar_t;
#endif

#define NULL ((void *)0)

#define PTRDIFF(a, b) ((ptrdiff_t)(a)-(ptrdiff_t)(b))

#define offsetof(stype, m) (size_t)(&(((stype *)0)->m))

#define att_asm(cmd, ...) __asm__ volatile (cmd __VA_ARGS__)
#define intel_asm(cmd, ...) __asm__ volatile (".intel_syntax noprefix\n" cmd "\n.att_syntax noprefix\n" __VA_ARGS__ ) 

#define break_point(...) intel_asm("int3", __VA_ARGS__ );

#endif //__STDDEF_H

///
