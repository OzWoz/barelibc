// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int raise(int sig)
{
	printf("Raising signal %d\n", sig);
	exit(EXIT_FAILURE);
	return 0;
}

///
