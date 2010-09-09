// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdlib.h>
#include <smp.h>

static volatile __atexit_t *__atexit_first = NULL;
static mutex_t __atexit_mutex = 0;

int atexit(void (*func)(void))
{
	__atexit_t *p = malloc(sizeof(__atexit_t));
	mutex_lock(&__atexit_mutex);
	p->next = (__atexit_t *)__atexit_first;
	p->type = __ATEXIT_TYPE_NOARG;
	p->fnc.noarg = func;
	__atexit_first = p;
	mutex_unlock(&__atexit_mutex);
	return 0;
}

int atexit_arg(void (*func)(void *))
{
	__atexit_t *p = malloc(sizeof(__atexit_t));
	mutex_lock(&__atexit_mutex);
	p->next = (__atexit_t *)__atexit_first;
	p->type = __ATEXIT_TYPE_ARG;
	p->fnc.arg = func;
	__atexit_first = p;
	mutex_unlock(&__atexit_mutex);
	return 0;
}

void exit(int ret)
{
	__atexit_t *p;
	for (;;) {
		mutex_lock(&__atexit_mutex);
		p = (__atexit_t *)__atexit_first;
		if (p == NULL) {
			mutex_unlock(&__atexit_mutex);
			break;
		}
		__atexit_first = p->next;
		mutex_unlock(&__atexit_mutex);

		switch (p->type) {
			case __ATEXIT_TYPE_NOARG:
				p->fnc.noarg();
				break;
			case __ATEXIT_TYPE_ARG:
				p->fnc.arg(p->arg);
				break;
		}
		free(p);
	}
	_Exit(ret);
}

///
