// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

//#define N 1299720 //100000 primes
//#define N 15485864 //1000000 primes
#define N 86028122 //5000000 primes

int main(void)
{
	int i, j;
	time_t start;
	bool *prime;
	start = time(NULL);

	prime = malloc(N*sizeof(bool));

	prime[0] = prime[1] = false;
	for (i = 2; i < N; i++) {
		prime[i] = true;
	}
	for (i = 2; i < N; i++) {
		for (j = 2*i; j < N; j += i) {
			prime[j] = false;
		}
	}
	for (i = 0, j = 0; i < N; i++) {
		if (prime[i]) j++;
	}

	free(prime);	

	printf("number of primes < %d: %d\n", N, j);
	printf("time: %d sec\n", (int)(difftime(time(NULL), start)+0.5));
	return 0;
}

///
