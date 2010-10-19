#include <__init.h>
#include <__os.h>

#ifndef __OS_MEMSIZE
	#define __OS_MEMSIZE (1024*1024*1024)
#endif

#undef main
#undef malloc
#undef free

void *malloc(unsigned long long);
void free(void *);

int main(int argc, char *argv[], char *envp[])
{
	int ret = 0;
	void *mem = malloc(__OS_MEMSIZE);
	ret = (int)__init(argc, argv, envp, (volatile void *)mem, __OS_MEMSIZE);
	free(mem);
	return ret;
}

///

