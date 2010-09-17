// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdio.h>

class test
{
public:
	test()
	{
		puts("constructor\n");
	}

	~test()
	{
		puts("destructor\n");
	}

	int add(int a, int b)
	{
		return a+b;
	}
};

test t1, t2;

void main(void)
{
	puts("main start\n");
	printf("4+7=%d, 2+5=%d\n", t1.add(4, 7), t2.add(2, 5));
	puts("main end\n");
}

///
