// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#ifndef ____OS_H
#define ____OS_H

#ifndef __OS_MEM_SIZE
#define __OS_MEM_SIZE (256*1024*1024)
#endif

#ifndef __OS_CORE_NUM
#define __OS_CORE_NUM 8
#endif

#ifndef __OS_STACK_SIZE
#define __OS_STACK_SIZE (2*1024*1024)
#endif

#ifndef __STDDEF_H
#include <stddef.h>
#endif

#define MAX_CORE_NUM 255

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1000000
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*__os_smp_proc_t)(void *);
void __os_smp_init(void);

void __os_print_char(char c);
void __os_print_newline(void);
void __os_get_timecounter(unsigned long long *ret);
void __os_smp_get_id(unsigned long long *ret);
void __os_smp_enqueue(__os_smp_proc_t proc, void *param, unsigned long long *ret);
void __os_smp_dequeue(__os_smp_proc_t *proc, void **param);
void __os_smp_wait(void);
void __os_smp_run(__os_smp_proc_t proc, void *param);

#ifdef __cplusplus
}
#endif

#endif //____OS_H

///
