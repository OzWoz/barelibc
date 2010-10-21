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
	unsigned i, j, k;
	unsigned s[M];
	unsigned char *v[M];
	for (i = 0; i < M; i++) {
		v[i] = NULL;
		s[i] = 0;
	}
	for (i = 0; i < T; i++) {
		srand(i+3);
		j = rand()%M;
		if (v[j]) {
			for (k = 0; k < s[j]; k++) {
				assert(v[j][k] == ((j^s[j])&0xff));
			}
		}
		s[j] = rand()%S;
		v[j] = realloc(v[j], s[j]);
		assert(s[j] == 0 || v[j] != NULL);
		memset(v[j], (j^s[j])&0xff, s[j]);
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

