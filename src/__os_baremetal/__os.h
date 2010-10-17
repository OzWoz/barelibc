// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#ifndef ____OS_H
#define ____OS_H

#ifndef __STDDEF_H
#include <stddef.h>
#endif

#define MAX_CORE_NUM 255

#define CLOCKS_PER_SEC 8

#ifndef ____OS_INC_H
#include <__os_inc.h>
#endif

#define __os_print_char(c) intel_asm(__b_print_char "call b_print_char", ::"a"(c) :"cc")
#define __os_print_newline() intel_asm(__b_print_newline "call b_print_newline", :::"cc")
#define __os_print_hex(l) intel_asm(__b_debug_dump_rax "call b_debug_dump_rax", ::"a"(l) :"cc")

#define __os_get_timecounter(ret) intel_asm(__b_get_timecounter "call b_get_timecounter", :"=a"(*(ret)) ::"cc")

#define __os_smp_get_id(ret) intel_asm(__b_smp_get_id "call b_smp_get_id", :"=a"(*(ret)) ::"cc")
#define __os_smp_enqueue(proc, param, ret) intel_asm(__b_smp_enqueue "call b_smp_enqueue; setc %b0; movzx %0, %b0", :"=r"(*(ret)) :"a"(proc), "S"(param) :"cc")
#define __os_smp_dequeue(proc, param) intel_asm(__b_smp_dequeue "call b_smp_dequeue", :"=a"(*(proc)), "=D"(*(param)) ::"cc")
#define __os_smp_wait() intel_asm(__b_smp_wait "call b_smp_wait", :::"cc")
#define __os_smp_run(proc, param) intel_asm(__b_smp_run "call b_smp_run", ::"a"(proc), "D"(param) :"cc", "memory", "rcx", "rdx", "rsi", "r8", "r9", "r10", "r11")

#endif //____OS_H

///
