#include "__os.h"

#undef putchar
#undef time

int putchar(int);
int time(int *);

void __os_print_char(char c)
{
	putchar(c);
}

void __os_print_newline(void)
{
	putchar('\n');
}

void __os_print_hex(unsigned long long n)
{
	int i;
	for (i = 0; i < 16; i++) {
		int j = (n>>(4*(15-i)))&0xf;
		putchar(j < 10 ? '0'+j : 'A'+j-10);
	}
}

void __os_get_timecounter(unsigned long long *ret)
{
	*ret = time(NULL)*CLOCKS_PER_SEC;
}

void __os_smp_get_id(unsigned long long *ret)
{
	*ret = 0;
}

void __os_smp_enqueue(void (*proc)(void *), void *param, unsigned long long *ret)
{
	proc(param);
    *ret = 0;
}

void __os_smp_dequeue(void (**proc)(void *), void **param)
{
	*proc = NULL;
    *param = NULL;
}

void __os_smp_wait(void)
{

}

void __os_smp_run(void (*proc)(void *), void *param)
{
	proc(param);
}

///
