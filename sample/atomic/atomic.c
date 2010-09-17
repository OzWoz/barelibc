// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <smp.h>
#include <assert.h>

volatile int x = 0;

int main(void)
{
	int ret;
    assert(x == 0);
    atomic_exchange(&x, 1, &ret);
    assert(ret == 0);
    assert(x == 1);
    atomic_compareexchange(&x, 2, 3, &ret);
    assert(x == 1);
    assert(ret == 1);
    atomic_compareexchange(&x, 1, 4, &ret);
    assert(x == 4);
    assert(ret == 1);
    atomic_add(&x, 5, &ret);
    assert(x == 9);
    assert(ret == 4);
    atomic_bitreset(&x, 3, &ret);
    assert(x == 1);
    assert(ret == 1);
    atomic_bitcomplement(&x, 2, &ret);
    assert(x == 5);
    assert(ret == 0);
    atomic_bittest(&x, 0, &ret);
    assert(x == 5);
    assert(ret == 1);
    atomic_bitset(&x, 2, &ret);
    assert(x == 5);
    assert(ret == 1);
    puts("all tests ok\n");
    return 0;
}

///
