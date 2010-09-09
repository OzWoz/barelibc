// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <time.h>

int main(void)
{
    time_t start = time(NULL);
    while (difftime(time(NULL), start) < 3);
  	return 0;
}

///
