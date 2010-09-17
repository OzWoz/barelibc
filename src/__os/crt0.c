#include <__init.h>
#include <__os.h>

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
