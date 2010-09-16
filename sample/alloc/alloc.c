// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdlib.h>
#include <assert.h>

#define N 1000000
void test1(void)
{
	int i, *v, *w;

	v = calloc(N, sizeof(int));
	assert(v != NULL);
	for (i = 0; i < N; i++) {
		assert(v[i] == 0);
	}
	for (i = 0; i < N; i++) {
		v[i] = N-i;
	}
	for (i = 0; i < N; i++) {
		assert(v[i] == N-i);
	}
	w = malloc(N*sizeof(int));
	for (i = 0; i < N; i++) {
		w[i] = ~v[i];
	}
	for (i = 0; i < N; i++) {
		assert((v[i]^w[i]) == (~0));
	}
	free(v);
	free(w);
}


#define M 1024
#define T 10000
#define S 10000
void test2(void)
{
	int i;
	void *v[M];
	for (i = 0; i < M; i++) {
		v[i] = NULL;	
	}
	for (i = 0; i < T; i++) {
		int j = rand()%M;
		v[j] = realloc(v[j], rand()%S);
	}
}

int main(void)
{
	test1();
	test2();
	puts("all tests ok\n");
	return 0;
}

///

