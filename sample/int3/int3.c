// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stddef.h>

int main(void)
{
	intel_asm("mov rax, cr0",);
	break_point();
  	return 0;
}

///
