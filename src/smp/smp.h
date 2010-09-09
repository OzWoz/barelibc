// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#ifndef __SMP_H
#define __SMP_H

#ifndef __STDDEF_H
#include <stddef.h>
#endif

#ifndef ____OS_H
#include <__os.h>
#endif

#define MAX_THREAD_NUM MAX_CORE_NUM


#ifdef __cplusplus
extern "C" {
#endif

#define atomic_exchange(addr, val, ret) intel_asm("lock xchg [%1], %0", :"=r"(*(ret)) :"r"(addr), "0"(val) :"memory")
#define atomic_compareexchange(addr, cmp, val, ret) intel_asm("lock cmpxchg [%1], %3", :"=a"(*(ret)) :"r"(addr), "a"(cmp), "r"(val) :"memory", "cc")
#define atomic_add(addr, val, ret) intel_asm("lock xadd [%1], %0", :"=r"(*(ret)) :"r"(addr), "0"(val) :"memory")
#define atomic_bittest(addr, bit, ret) intel_asm("bt [%1], %2; setc %b0; movzx %0, %b0", :"=r"(*(ret)) :"r"(addr), "r"(bit) :"cc")
#define atomic_bitset(addr, bit, ret) intel_asm("lock bts [%1], %2; setc %b0; movzx %0, %b0", :"=r"(*(ret)) :"r"(addr), "r"(bit) :"memory", "cc")
#define atomic_bitreset(addr, bit, ret) intel_asm("lock btr [%1], %2; setc %b0; movzx %0, %b0", :"=r"(*(ret)) :"r"(addr), "r"(bit) :"memory", "cc")
#define atomic_bitcomplement(addr, bit, ret) intel_asm("lock btc [%1], %2; setc %b0; movzx %0, %b0", :"=r"(*(ret)) :"r"(addr), "r"(bit) :"memory", "cc")
/*
#define atomic_exchange(addr, val, ret) (*(ret) = __sync_lock_test_and_set((addr), (val)))
#define atomic_compareexchange(addr, cmp, val, ret) (*(ret) = __sync_val_compare_and_swap((addr), (cmp), (val)))
#define atomic_add(addr, val, ret) (*(ret) = __sync_fetch_and_add((addr), (val)))
*/

typedef volatile unsigned long long mutex_t;
void mutex_lock(mutex_t *m);
unsigned mutex_trylock(mutex_t *m);
void mutex_unlock(mutex_t *m);

typedef volatile unsigned long long reentrant_mutex_t;
void reentrant_mutex_lock(reentrant_mutex_t *m);
unsigned reentrant_mutex_trylock(reentrant_mutex_t *m);
void reentrant_mutex_unlock(reentrant_mutex_t *m);

typedef void (*thread_fnc)(void *);
void thread_create(thread_fnc func, void *param);
void thread_wait(void);
unsigned thread_current_id(void);

#ifdef __cplusplus
}
#endif

#endif //__SMP_H

///
