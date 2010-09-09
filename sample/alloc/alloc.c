// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdlib.h>
#include <assert.h>

#define N 1000000

int main(void)
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

	puts("all tests ok\n");
	return 0;
}

///

