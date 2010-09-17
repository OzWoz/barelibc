// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <smp.h>
#include <__os.h>

unsigned thread_current_id(void)
{
	unsigned ret;
	__os_smp_get_id(&ret);
	return ret;
}

void thread_create(thread_fnc func, void *param)
{
	unsigned bad;
	unsigned long long proc;
	void *procparam;
	for (;;) {
		__os_smp_enqueue(func, param, &bad);
		if (!bad) break;
		__os_smp_dequeue(&proc, &procparam);
		if (proc != 0) {
			do {
				__os_smp_enqueue(func, param, &bad);
			} while (bad);
			__os_smp_run(proc, procparam);
		}
	}
}

void thread_wait(void)
{
	unsigned long long proc;
	void *procparam;
	for (;;) {
		__os_smp_dequeue(&proc, &procparam);
		if (proc == 0) break;
        __os_smp_run(proc, procparam);
	}
	__os_smp_wait();
}

///

