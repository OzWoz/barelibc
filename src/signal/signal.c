// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int BLC_PREFIX(raise)(int sig)
{
	char linestr[20];
	fputs("Raising signal ", stderr);
	itoa(sig, linestr, 10);
	fputs(linestr, stderr);
	fputs("\n", stderr);
	exit(EXIT_FAILURE);
	return 0;
}

///
