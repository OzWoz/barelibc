// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdlib.h>
#include <setjmp.h>

void _Exit(int ret)
{
	longjmp(__exit_buf, ret ? ret : NORMAL_EXIT_CODE);
}

///
