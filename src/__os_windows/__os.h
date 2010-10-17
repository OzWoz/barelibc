// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#ifndef ____OS_H
#define ____OS_H

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

void __os_print_char(char c);
void __os_print_newline(void);
void __os_print_hex(unsigned long long n);
void __os_get_timecounter(unsigned long long *ret);
void __os_smp_get_id(unsigned long long *ret);
void __os_smp_enqueue(void (*proc)(void *), void *param, unsigned long long *ret);
void __os_smp_dequeue(void (**proc)(void *), void **param);
void __os_smp_wait(void);
void __os_smp_run(void (*proc)(void *), void *param);

#ifdef __cplusplus
}
#endif

#endif //____OS_H

///
