// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#ifndef __SETJMP_H
#define __SETJMP_H

#ifndef __STDDEF_H
#include <stddef.h>
#endif

typedef struct {
	unsigned long long rbx;
	unsigned long long rbp;
	unsigned long long r12;
	unsigned long long r13;
	unsigned long long r14;
	unsigned long long r15;
	unsigned long long rsp;
} jmp_buf;

#ifdef __cplusplus
extern "C" {
#endif

int __setjmp(jmp_buf *env);
void __longjmp(jmp_buf *env, int val);

#ifdef __cplusplus
}
#endif

#define setjmp(env) __setjmp(&(env))
#define longjmp(env, val) __longjmp(&(env), (val))

#endif //__SETJMP_H

///
