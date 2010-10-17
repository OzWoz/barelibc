// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdlib.h>
#include <smp.h>

#ifdef __os_baremetal
void *__dso_handle = NULL;
#endif

static __atexit_t * volatile __atexit_first = NULL;
static mutex_t __atexit_mutex = 0;

int BLC_PREFIX(atexit)(void (*func)(void))
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

int BLC_PREFIX(atexit_arg)(void (*func)(void *), void *arg)
{
	__atexit_t *p = malloc(sizeof(__atexit_t));
	mutex_lock(&__atexit_mutex);
	p->next = (__atexit_t *)__atexit_first;
	p->type = __ATEXIT_TYPE_ARG;
	p->fnc.arg = func;
	p->arg = arg;
	__atexit_first = p;
	mutex_unlock(&__atexit_mutex);
	return 0;
}

#ifdef __os_baremetal
int __cxa_atexit(void (*func)(void *), void *arg, void *dso_handle)
{
	return atexit_arg(func, arg);
}
#endif

void BLC_PREFIX(exit)(int ret)
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
