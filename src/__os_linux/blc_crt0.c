// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <__init.h>
#include <__os.h>

#undef main
#undef malloc
#undef free

void *malloc(unsigned long long);
void free(void *);

int main(int argc, char *argv[], char *envp[])
{
	int ret;
	void *mem, *stack;
	mem = malloc(__OS_MEM_SIZE);
	stack = malloc(__OS_CORE_NUM*__OS_STACK_SIZE);
	__os_smp_init(stack);
	ret = (int)__init(argc, argv, envp, (volatile void *)mem, __OS_MEM_SIZE);
	__os_smp_exit();
	free(stack);
	free(mem);
	return ret;
}

///

