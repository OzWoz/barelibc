// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <__init.h>
#include <__os.h>

#define __OS_MEM_PAGE_SIZE 0x200000
#define __os_mem_get_free(ret) intel_asm(__b_mem_get_free "call b_mem_get_free", :"=c"(*(ret)) ::"cc")
#define __os_mem_allocate(numpage, ret) intel_asm(__b_mem_allocate "call b_mem_allocate", :"=a"(*(ret)) :"c"(numpage) :"cc")
#define __os_mem_release(addr, numpage) intel_asm(__b_mem_release "call b_mem_release", ::"a"(addr), "c"(numpage) :"cc")

#define __os_get_argc(ret) intel_asm(__b_get_argc "call b_get_argc; movzx rax, al", :"=a"(*(ret)) ::"cc")
#define __os_get_argv(num, ret) intel_asm(__b_get_argv "call b_get_argv", :"=S"(*(ret)) :"a"(num) :"cc")

long long __start(void)
{
	unsigned num, argc, ret, i;
	volatile void *mem;
	char *env = NULL;
	char *argv[256];

	__os_mem_get_free(&num);
	__os_mem_allocate(num, &mem);

	__os_get_argc(&argc);
	for (i = 0; i < argc; i++) {
		__os_get_argv(i, argv+i);
	}

	ret = __init(argc, argv, &env, mem, num*__OS_MEM_PAGE_SIZE);

	__os_mem_release(mem, num);

	return ret;
}

///
