// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ht7_noval.h"

//len is number of unsigneds
static inline unsigned MurmurHash(const unsigned *data, unsigned len, unsigned seed)
{
	const unsigned m = 0x5bd1e995;
	unsigned h = seed ^ len;

	while(len)
	{
		unsigned k = *data;
		k *= m; 
		k ^= k >> 24; 
		k *= m; 
		h *= m; 
		h ^= k;
		data++;
		len--;
	}
	
	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return h;
} 

static unsigned keyhash(void *param, Htkey key)
{
	return MurmurHash(&key, 1, 0xe164ab8a);	
}

static int keyeq(void *param, Htkey a, Htkey b)
{
	return a == b;
}

#define T 50000000
#define M 5000000

int main(void)
{
	unsigned i;
	time_t start;
	Ht *ht;
	start = time(NULL);
	ht = htalloc(keyhash, keyeq, NULL);
	for (i = 0; i < T; i++) {
    	htinsert(ht, rand()%M);
	}
	htfree(ht);
	printf("time: %d sec\n", (int)(difftime(time(NULL), start)+0.5));
	return 0;
}

///
