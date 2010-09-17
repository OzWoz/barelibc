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
#define __os_smp_enqueue(proc, ret) intel_asm(__b_smp_enqueue "call b_smp_enqueue; setc %b0; movzx %0, %b0", :"=r"(*(ret)) :"a"(proc) :"cc")
#define __os_smp_dequeue(proc) intel_asm(__b_smp_dequeue "call b_smp_dequeue", :"=a"(*(proc)) ::"cc")
#define __os_smp_wait() intel_asm(__b_smp_wait "call b_smp_wait", :::"cc")
#define __os_smp_run(proc) intel_asm(__b_smp_run "call b_smp_run", ::"a"(proc) :"cc")

#define __OS_MEM_PAGE_SIZE 0x200000
#define __os_mem_get_free(ret) intel_asm(__b_mem_get_free "call b_mem_get_free", :"=c"(*(ret)) ::"cc")
#define __os_mem_allocate(numpage, ret) intel_asm(__b_mem_allocate "call b_mem_allocate", :"=a"(*(ret)) :"c"(numpage) :"cc")
#define __os_mem_release(addr, numpage) intel_asm(__b_mem_release "call b_mem_release", ::"a"(addr), "c"(numpage) :"cc")

#define __os_get_argc(ret) intel_asm(__b_get_argc "call b_get_argc; movzx rax, al", :"=a"(*(ret)) ::"cc")
#define __os_get_argv(num, ret) intel_asm(__b_get_argv "call b_get_argv", :"=S"(*(ret)) :"a"(num) :"cc")

#endif //____OS_H

///
