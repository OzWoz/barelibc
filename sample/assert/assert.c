// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <assert.h>

int main(void)
{
	puts("there should be 3 goods, 1 bad, 1 assertion failure\n");
	puts("good\n");
	assert(1);
	puts("good\n");
	assert(1 != 2);
	puts("good\n");
	assert(1 < 2);
	puts("bad\n");
	assert(12 < 3);
	puts("good\n");
	assert(10 > 2);
    return 0;
}

///
