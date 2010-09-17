#include <__init.h>
#include <__os.h>
#include <setjmp.h>
#include <stdlib.h>

jmp_buf __exit_buf;

long long __start(void)
{
	unsigned num, ret, argc, i;
	volatile void *mem;
	char *env = NULL;
	char *argv[256];

	__os_mem_get_free(&num);
	__os_mem_allocate(num, &mem);

	__init(mem, num*__OS_MEM_PAGE_SIZE);

	if ((ret = setjmp(__exit_buf)) == 0) {
		__os_get_argc(&argc);
		for (i = 0; i < argc; i++) {
			__os_get_argv(i, argv+i);
		}
		ret = main(argc, argv, &env);
	}
	if (ret == NORMAL_EXIT_CODE) ret = 0;

	__os_mem_release(mem, num);

	return ret;
}

///
