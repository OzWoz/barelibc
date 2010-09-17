// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdlib.h>
#include <setjmp.h>

extern unsigned __exit_called;
extern jmp_buf __exit_buf;

void _Exit(int ret)
{
	__exit_called = 1;
	longjmp(__exit_buf, ret ? ret : NORMAL_EXIT_CODE);
}

///
