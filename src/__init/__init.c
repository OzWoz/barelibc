// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <__init.h>

jmp_buf __exit_buf;
unsigned __exit_called = 0;

typedef void (*voidfnctype)(void);
extern voidfnctype __start_ctors, __end_ctors, __start_dtors, __end_dtors;

long long __init(int argc, char *argv[], char *envp[], volatile void *heap_ptr, size_t heap_size)
{
	int ret;
	voidfnctype *fnc;

	srand(1);
	__init_alloc(heap_ptr, heap_size);

	for (fnc = &__start_ctors; fnc < &__end_ctors; fnc++) (*fnc)();

	ret = setjmp(__exit_buf);
	if (ret == 0) ret = main(argc, argv, envp);
	if (ret == NORMAL_EXIT_CODE) ret = 0;

	if (!__exit_called) exit(ret);

	for (fnc = &__start_dtors; fnc < &__end_dtors; fnc++) (*fnc)();

	return (long long)ret;
}

///
