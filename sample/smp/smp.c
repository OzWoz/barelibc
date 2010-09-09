// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <smp.h>
#include <stdio.h>
#include <time.h>

static time_t mainstart;

#define TIME_NOW (int)(difftime(time(NULL), mainstart)+0.5)

void func(void *param)
{
	time_t start = time(NULL);
	printf("starting thread %d at time %d\n", thread_current_id(), TIME_NOW);
	while (difftime(time(NULL), start) < 4);
	printf("ending thread %d at time %d\n", thread_current_id(), TIME_NOW);
}

int main(void)
{
	int i;
	mainstart = time(NULL);
	printf("starting main thread %d at time %d\n", thread_current_id(), TIME_NOW);
	for (i = 0; i < 10; i++) {
		thread_create(func, NULL);
	}
	printf("starting to wait at time %d\n", TIME_NOW);
	thread_wait();
	printf("ending main thread %d at time %d\n", thread_current_id(), TIME_NOW);
	return 0;
}

///
