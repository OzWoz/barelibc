// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdarg.h>
#include <assert.h>

int add(int n, ...)
{
	int ret = 0, i;
	va_list args;
	va_start(args, n);
	for (i = 0; i < n; i++) {
		int next = va_arg(args, int);
		ret += next;
	}
	va_end(args);	
	return ret;
}

int main(void)
{
	assert(add(0) == 0);
	assert(add(1, 1) == 1);
	assert(add(2, 1, 2) == 3);
	assert(add(3, -2, 0, 7) == 5);
	assert(add(10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10) == 55);
	puts("all tests ok\n");
	return 0;
}

///
