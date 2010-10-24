// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include "__os.h"
#include <smp.h>

typedef unsigned long time_t;
struct timespec {
	time_t tv_sec;
	long tv_nsec;
};
int nanosleep(const struct timespec *, struct timespec *);

static inline void Sleep(unsigned msec)
{
	struct timespec t;
	t.tv_sec = 0;
	t.tv_nsec = msec*1000;
	nanosleep(&t, NULL);
}

int putchar(int);
int time(int *);

int clone(int (*)(void *), void *, int, void *, ...);

#define SIGCHLD 17
#define CLONE_VM 256

void __os_print_char(char c)
{
	putchar(c);
}

void __os_print_newline(void)
{
	putchar('\n');
}

void __os_get_timecounter(unsigned long long *ret)
{
	*ret = time(NULL)*CLOCKS_PER_SEC;
}

typedef struct {
	__os_smp_proc_t proc;
	void *param;
} queue_t;

#define QUEUELEN 256

static mutex_t queuemutex;
static volatile queue_t queue[QUEUELEN];
static volatile unsigned queuestart, queueend;

typedef struct {
	void *stack;
	unsigned id;
	unsigned status;
} core_t;

static volatile core_t cores[__OS_CORE_NUM];
static volatile unsigned coreind[__OS_CORE_NUM];

void __os_smp_get_id(unsigned long long *ret)
{
	unsigned i;
	void *stack;
	intel_asm("mov %0, rsp", :"=r"(stack));
	for (i = 0; i < __OS_CORE_NUM; i++) {
		if (cores[coreind[i]].stack >= stack) {
			*ret = i;
			return;
		}
	}
	*ret = 0; //error
}

void __os_smp_enqueue(__os_smp_proc_t proc, void *param, unsigned long long *ret)
{
	if (queue[queueend].proc != NULL) {
		*ret = 1;
		return;
	}
	mutex_lock(&queuemutex);
	if (queue[queueend].proc == NULL) {
		queue[queueend].proc = proc;
		queue[queueend].param = param;
		if (++queueend == QUEUELEN) queueend = 0;
	    *ret = 0;
	} else {
		*ret = 1;
	}
	mutex_unlock(&queuemutex);
}

void __os_smp_dequeue(__os_smp_proc_t *proc, void **param)
{
	if (queue[queuestart].proc == NULL) {
		*proc = NULL;
        *param = NULL;
        return;
	}
	mutex_lock(&queuemutex);
    if (queue[queuestart].proc == NULL) {
		*proc = NULL;
        *param = NULL;
    } else {
	    *proc = queue[queuestart].proc;
    	*param = queue[queuestart].param;
		queue[queuestart].proc = NULL;
		queue[queuestart].param = NULL;
		if (++queuestart == QUEUELEN) queuestart = 0;
    }
	mutex_unlock(&queuemutex);
}

static inline void __os_smp_dequeue_status(__os_smp_proc_t *proc, void **param, volatile unsigned *status)
{
	if (queue[queuestart].proc == NULL) {
		*proc = NULL;
        *param = NULL;
        return;
	}
	mutex_lock(&queuemutex);
    if (queue[queuestart].proc == NULL) {
		*proc = NULL;
        *param = NULL;
    } else {
	    *proc = queue[queuestart].proc;
    	*param = queue[queuestart].param;
		queue[queuestart].proc = NULL;
		queue[queuestart].param = NULL;
		if (++queuestart == QUEUELEN) queuestart = 0;
        *status = 1;
    }
	mutex_unlock(&queuemutex);
}

void __os_smp_wait(void)
{
	unsigned i;
	while (queue[queuestart].proc != NULL) Sleep(1);
wait:
	for (i = 1; i < __OS_CORE_NUM; i++) {
		if (cores[i].status == 1) {
			Sleep(1);
			goto wait;
		}
	}
}

void __os_smp_run(__os_smp_proc_t proc, void *param)
{
	proc(param);
}


static int corefunc(void *param)
{
	volatile core_t *core = param;

	intel_asm("mov %0, rsp", :"=r"(core->stack));
	core->status = 0;

	for (;;) {
		__os_smp_proc_t proc;
		void *param;
		if (core->status == 2) break;
		__os_smp_dequeue_status(&proc, &param, &core->status);
		if (proc != NULL) {
			__os_smp_run(proc, param);
			core->status = 0;
		} else {
			Sleep(1);
		}
	}
	return 0;
}

void __os_smp_init(void *stack)
{
	unsigned i, j;

	queuemutex = 0;
	queuestart = 0;
	queueend = 0;
	for (i = 0; i < QUEUELEN*sizeof(queue_t); i++) ((volatile char *)queue)[i] = 0;

	intel_asm("mov %0, rsp", :"=r"(cores[0].stack));
	cores[0].status = 1;
	
	for (i = 1; i < __OS_CORE_NUM; i++) {
		coreind[i] = i;
		cores[i].status = 1;
		clone(corefunc, stack+i*__OS_STACK_SIZE-4, SIGCHLD|CLONE_VM, (void *)(cores+i));
	}
	__os_smp_wait();

	for (i = 0; i < __OS_CORE_NUM; i++) {
		for (j = i+1; j < __OS_CORE_NUM; j++) {
			if (cores[coreind[i]].stack > cores[coreind[j]].stack) {
				volatile unsigned t;
				t = coreind[i];
				coreind[i] = coreind[j];
				coreind[j] = t;
			}
		}
	}
}

void __os_smp_exit(void)
{
	unsigned i;

	for (i = 0; i < __OS_CORE_NUM; i++) {
		cores[i].status = 2;
	}
}

///
