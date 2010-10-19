// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

//need SL_PREFIX, SL_ATTR, SL_STATICATTR, SL_HASBLINK, SL_KEYSIZE, SL_VALUESIZE, SL_CMP, SL_RAND, SL_KEYCPY, SL_VALUECPY, SL_REALLOC, SL_PRINT

#define SL_LINK(k) pl->links[0][(k)*pl->itemsize[0]]
#define SL_BLINK(k) pl->links[0][(k)*pl->itemsize[0]+1]
#define SL_KEY(k) (pl->links[0]+(k)*pl->itemsize[0]+1+(SL_HASBLINK ? 1 : 0))
#define SL_VALUE(k) (pl->links[0]+(k)*pl->itemsize[0]+1+(SL_HASBLINK ? 1 : 0)+SL_KEYSIZE)
#define SL_NEXTEMPTY(k) SL_LINK(k)

#define SL_HEAD(l) SL_LINK(0)
#define SL_BHEAD(l) SL_BLINK(0)

#define SL_CEIL4(x) (((x)+3)&~3)

#define SL_EXPECTEDNUM(n) (n)
#define SL_EXPECTEDSIZE(n) (((SL_HASBLINK)?2:1)*(1200+SL_EXPECTEDNUM(n))+(SL_KEYSIZE+SL_VALUESIZE)*((n)+100))

SL_ATTR unsigned SL_PREFIX(head)(void)
{
	return 0;
}

SL_ATTR unsigned SL_PREFIX(size)(unsigned num)
{
	return SL_EXPECTEDSIZE(num);
}

SL_ATTR void SL_PREFIX(clear)(SL_PREFIX(t) *pl)
{
	unsigned j;
	if (pl->allocated[0] != 0) {
		for (j = 1; j < pl->allocated[0]-1; j++) {
			SL_NEXTEMPTY(j) = j+1;
		}
		SL_NEXTEMPTY(pl->allocated[0]-1) = UNONE;
		pl->empty[0] = 1;
	} else {
		pl->empty[0] = UNONE;
	}
	SL_HEAD(0) = 0;
	#if SL_HASBLINK
	SL_BHEAD(0) = 0;
	#endif
	pl->num = 0;
}

/* size is number of unsigneds in buf */
SL_ATTR unsigned SL_PREFIX(init)(SL_PREFIX(t) *pl, unsigned *buf, unsigned size, void *callbackptr)
{
	pl->itemsize[0] = SL_KEYSIZE + SL_VALUESIZE + 1 + (SL_HASBLINK ? 1 : 0);
	pl->links[0] = NULL;
	if (buf != NULL) {
		pl->isstatic = 1;
		pl->allocated[0] = size/pl->itemsize[0];
		pl->links[0] = buf;
	} else {
		unsigned *newptr;
		pl->callbackptr = callbackptr;
		pl->isstatic = 0;
		pl->allocated[0] = 4;
		newptr = SL_REALLOC(pl->callbackptr, NULL, 4*pl->itemsize[0]*sizeof(unsigned));
		if (newptr == NULL) {
			return UERROR;
		}
		pl->links[0] = newptr;
	}
	SL_PREFIX(clear)(pl);
	return 0;
}

SL_ATTR void SL_PREFIX(exit)(SL_PREFIX(t) *pl)
{
	if (!pl->isstatic) {
		if (pl->links[0] != NULL) SL_REALLOC(pl->callbackptr, pl->links[0], 0);
	}
}

SL_ATTR unsigned SL_PREFIX(insert)(SL_PREFIX(t) *pl, unsigned *newkey, unsigned *newvalue, unsigned *found)
{
	unsigned i, prev = 0, k;
	for (i = SL_LINK(prev); i != 0; i = SL_LINK(prev)) {
		int ret;
		ret = SL_CMP(pl->callbackptr, SL_KEY(i), newkey);
		if (ret == 0) {
			if (found) *found = 1;
			#if SL_VALUESIZE
			SL_VALUECPY(SL_VALUE(i), newvalue, SL_VALUESIZE*sizeof(unsigned));
			#endif
			return i;
		}
		if (ret > 0) break;
		prev = i;
	}
	if (pl->empty[0] == UNONE) {
		unsigned oldalloc;
		if (pl->isstatic) {
			return UERROR;
		}
		oldalloc = pl->allocated[0];
		pl->allocated[0] = SL_CEIL4((pl->allocated[0]+1)*3/2);
		pl->links[0] = SL_REALLOC(pl->callbackptr, pl->links[0], pl->allocated[0]*pl->itemsize[0]*sizeof(unsigned));
		if (pl->links[0] == NULL) {
			return UERROR;
		}
		for (i = oldalloc; i < pl->allocated[0]-1; i++) {
			SL_NEXTEMPTY(i) = i+1;
		}
		SL_NEXTEMPTY(pl->allocated[0]-1) = UNONE;
		pl->empty[0] = oldalloc;
	}
	k = pl->empty[0];
	pl->empty[0] = SL_NEXTEMPTY(k);
	SL_KEYCPY(SL_KEY(k), newkey, SL_KEYSIZE*sizeof(unsigned));
	#if SL_VALUESIZE
	SL_VALUECPY(SL_VALUE(k), newvalue, SL_VALUESIZE*sizeof(unsigned));
	#endif
	pl->num++;
	SL_LINK(k) = SL_LINK(prev);
	SL_LINK(prev) = k;
	#if SL_HASBLINK
	SL_BLINK(k) = prev;
	SL_BLINK(SL_LINK(k)) = k;
	#endif
	if (found) *found = 0;
	return k;
}

SL_STATICATTR unsigned SL_PREFIX(searchinner)(SL_PREFIX(t) *pl, void *searchkey, unsigned *found, unsigned *p)
{
	unsigned i, prev = 0;
	for (i = SL_LINK(prev); i != 0; i = SL_LINK(prev)) {
		int ret;
		ret = SL_CMP(pl->callbackptr, SL_KEY(i), searchkey);
		if (ret == 0) {
			if (found) *found = 1;
			return i;
		}
		if (ret > 0) break;
		prev = i;
	}
	if (found) *found = 0;
	if (p) *p = prev;
	return UNOTFOUND;
}

SL_ATTR unsigned SL_PREFIX(search)(SL_PREFIX(t) *pl, void *searchkey)
{
	return SL_PREFIX(searchinner)(pl, searchkey, NULL, NULL);
}

SL_ATTR unsigned SL_PREFIX(psearch)(SL_PREFIX(t) *pl, void *searchkey, unsigned *found)
{
	unsigned ret, prev = 0;
	ret = SL_PREFIX(searchinner)(pl, searchkey, found, &prev);
	if (ret != UNOTFOUND) return ret;
	ret = prev;
	return ret == 0 ? UNOTFOUND : ret;
}

SL_ATTR unsigned SL_PREFIX(nsearch)(SL_PREFIX(t) *pl, void *searchkey, unsigned *found)
{
	unsigned ret, prev = 0;
	ret = SL_PREFIX(searchinner)(pl, searchkey, found, &prev);
	if (ret != UNOTFOUND) return ret;
	ret = SL_LINK(prev);
	return ret == 0 ? UNOTFOUND : ret;
}

SL_ATTR void SL_PREFIX(delete)(SL_PREFIX(t) *pl, unsigned k, unsigned *found)
{
	unsigned i, prev = 0, ifound = 0;
	for (i = SL_LINK(prev); i != 0; i = SL_LINK(prev)) {
		if (i == k) break;
		prev = i;
	}
	if (i == k) {
		ifound = 1;
		SL_LINK(prev) = SL_LINK(k);
		#if SL_HASBLINK
		SL_BLINK(SL_LINK(prev)) = prev;
		#endif
		SL_NEXTEMPTY(k) = pl->empty[0];
		pl->empty[0] = k;
		pl->num--;
	}
	if (found) *found = ifound;
}

/* returns first if k = SL_PREFIX(head)*/
SL_ATTR unsigned SL_PREFIX(next)(SL_PREFIX(t) *pl, unsigned k)
{
	unsigned ret;
	ret = SL_LINK(k);
	return ret == 0 ? UNOTFOUND : ret;
}

/* returns last if k = SL_PREFIX(head)*/
SL_ATTR unsigned SL_PREFIX(prev)(SL_PREFIX(t) *pl, unsigned k)
{
	#if SL_HASBLINK
	{
		unsigned ret;
		ret = SL_BLINK(k);
		return ret == 0 ? UNOTFOUND : ret;
	}
	#else
	{
		unsigned i, prev = 0;
		for (i = SL_LINK(prev); i != 0; i = SL_LINK(prev)) {
			if (i == k) break;
			prev = i;
		}
		return prev == 0 ? UNOTFOUND : prev;
	}
	#endif
}

SL_ATTR unsigned *SL_PREFIX(getkey)(SL_PREFIX(t) *pl, unsigned k)
{
	return SL_KEY(k);
}

SL_ATTR unsigned *SL_PREFIX(getvalue)(SL_PREFIX(t) *pl, unsigned k)
{
	return SL_VALUE(k);
}

SL_ATTR unsigned SL_PREFIX(num)(SL_PREFIX(t) *pl)
{
	return pl->num;
}

#ifdef SL_PRINT
SL_ATTR void SL_PREFIX(print)(SL_PREFIX(t) *pl)
{
}
#endif

///
