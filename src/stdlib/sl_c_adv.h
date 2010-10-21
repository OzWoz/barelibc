// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

//need SL_PREFIX, SL_ATTR, SL_STATICATTR, SL_HASBLINK, SL_KEYSIZE, SL_VALUESIZE, SL_CMP, SL_RAND, SL_KEYCPY, SL_VALUECPY, SL_REALLOC, SL_PRINT

#define SL_P 1580030169 /* 2^32*1/e */

#define SL_LINK(klevel, kofs, l) pl->links[klevel][(kofs)*pl->itemsize[klevel]+l]
#define SL_BLINK(klevel, kofs, l) pl->links[klevel][(kofs)*pl->itemsize[klevel]+(klevel)+1+l]
#define SL_KEY(klevel, kofs) (pl->links[klevel]+(kofs)*pl->itemsize[klevel]+(klevel)+1+(SL_HASBLINK ? (klevel)+1 : 0))
#define SL_VALUE(klevel, kofs) (pl->links[klevel]+(kofs)*pl->itemsize[klevel]+(klevel)+1+(SL_HASBLINK ? (klevel)+1 : 0)+SL_KEYSIZE)
#define SL_NEXTEMPTY(klevel, kofs) SL_LINK(klevel, kofs, 0)

/* level0: 00... */
/* level1: 01... */
/* level2: 100... */
/* level3: 101... */
/* level4+: 11lllll... lllll=5-bit level */
/*
#define SL_MIX(klevel, kofs) \
((klevel) == 0 ? (kofs) : \
((klevel) == 1 ? (kofs)|0x40000000 : \
((klevel) == 2 ? (kofs)|0x80000000 : \
((klevel) == 3 ? (kofs)|0xA0000000 : \
((kofs)|0xC0000000|((klevel)<<25))))))

#define SL_SPLIT(k, klevel, kofs) { \
	if (((k)&0xC0000000) == 0) { (klevel) = 0; (kofs) = (k); } \
	else if (((k)&0xC0000000) == 0x40000000) { (klevel) = 1; (kofs) = (k)&0x3FFFFFFF; } \
	else if (((k)&0xE0000000) == 0x80000000) { (klevel) = 2; (kofs) = (k)&0x1FFFFFFF; } \
	else if (((k)&0xE0000000) == 0xA0000000) { (klevel) = 3; (kofs) = (k)&0x1FFFFFFF; } \
	else { (klevel) = ((k)&0x3FFFFFFF)>>25; (kofs) = (k)&0x01FFFFFF; } \
}
*/

/* level0: ...00 */
/* level1: ...01 */
/* level2: ...010 */
/* level3: ...110 */
/* level4+: ...lllll11 lllll=5-bit level */

#define SL_MIX(klevel, kofs) \
((klevel) == 0 ? ((kofs)<<2) : \
	((klevel) == 1 ? ((kofs)<<2)|0x00000001 : \
	((klevel) == 2 ? ((kofs)<<3)|0x00000002 : \
	((klevel) == 3 ? ((kofs)<<3)|0x00000006 : \
	(((kofs)<<7)|0x00000003|(((klevel)<<2)))))))

#define SL_SPLIT(k, klevel, kofs) { \
	if (((k)&0x00000003) == 0) { (klevel) = 0; (kofs) = (k)>>2; } \
	else if (((k)&0x00000003) == 0x00000001) { (klevel) = 1; (kofs) = (k)>>2; } \
	else if (((k)&0x00000007) == 0x00000002) { (klevel) = 2; (kofs) = (k)>>3; } \
	else if (((k)&0x00000007) == 0x00000006) { (klevel) = 3; (kofs) = (k)>>3; } \
	else { (klevel) = ((k)&0x0000007F)>>2; (kofs) = (k)>>7; } \
}


/* level  0: ...0 */
/* level  1: ...01 */
/* level  2: ...011 */
/* level  3: ...0111 */
/* level  4: ...01111 */
/* level 23: ...011111111111111111111111 */
/*
#define SL_MIX(klevel, kofs) \
((klevel) ==  0 ? ((kofs)<< 1) : \
((klevel) ==  1 ? ((kofs)<< 2)|0x00000001 : \
((klevel) ==  2 ? ((kofs)<< 3)|0x00000003 : \
((klevel) ==  3 ? ((kofs)<< 4)|0x00000007 : \
((klevel) ==  4 ? ((kofs)<< 5)|0x0000000F : \
((klevel) ==  5 ? ((kofs)<< 6)|0x0000001F : \
((klevel) ==  6 ? ((kofs)<< 7)|0x0000003F : \
((klevel) ==  7 ? ((kofs)<< 8)|0x0000007F : \
((klevel) ==  8 ? ((kofs)<< 9)|0x000000FF : \
((klevel) ==  9 ? ((kofs)<<10)|0x000001FF : \
((klevel) == 10 ? ((kofs)<<11)|0x000003FF : \
((klevel) == 11 ? ((kofs)<<12)|0x000007FF : \
((klevel) == 12 ? ((kofs)<<13)|0x00000FFF : \
((klevel) == 13 ? ((kofs)<<14)|0x00001FFF : \
((klevel) == 14 ? ((kofs)<<15)|0x00003FFF : \
((klevel) == 15 ? ((kofs)<<16)|0x00007FFF : \
((klevel) == 16 ? ((kofs)<<17)|0x0000FFFF : \
((klevel) == 17 ? ((kofs)<<18)|0x0001FFFF : \
((klevel) == 18 ? ((kofs)<<19)|0x0003FFFF : \
((klevel) == 19 ? ((kofs)<<20)|0x0007FFFF : \
((klevel) == 20 ? ((kofs)<<21)|0x000FFFFF : \
((klevel) == 21 ? ((kofs)<<22)|0x001FFFFF : \
((klevel) == 22 ? ((kofs)<<23)|0x003FFFFF : \
(((kofs)<<24)|0x007FFFFF))))))))))))))))))))))))


#define SL_SPLIT(k, klevel, kofs) \
if (((k)&0x00000001) == 0) { (klevel) = 0; (kofs) = (k)>>1; } \
else if (((k)&0x00000002) == 0) { (klevel) =  1; (kofs) = (k)>> 2; } \
else if (((k)&0x00000004) == 0) { (klevel) =  2; (kofs) = (k)>> 3; } \
else if (((k)&0x00000008) == 0) { (klevel) =  3; (kofs) = (k)>> 4; } \
else if (((k)&0x00000010) == 0) { (klevel) =  4; (kofs) = (k)>> 5; } \
else if (((k)&0x00000020) == 0) { (klevel) =  5; (kofs) = (k)>> 6; } \
else if (((k)&0x00000040) == 0) { (klevel) =  6; (kofs) = (k)>> 7; } \
else if (((k)&0x00000080) == 0) { (klevel) =  7; (kofs) = (k)>> 8; } \
else if (((k)&0x00000100) == 0) { (klevel) =  8; (kofs) = (k)>> 9; } \
else if (((k)&0x00000200) == 0) { (klevel) =  9; (kofs) = (k)>>10; } \
else if (((k)&0x00000400) == 0) { (klevel) = 10; (kofs) = (k)>>11; } \
else if (((k)&0x00000800) == 0) { (klevel) = 11; (kofs) = (k)>>12; } \
else if (((k)&0x00001000) == 0) { (klevel) = 12; (kofs) = (k)>>13; } \
else if (((k)&0x00002000) == 0) { (klevel) = 13; (kofs) = (k)>>14; } \
else if (((k)&0x00004000) == 0) { (klevel) = 14; (kofs) = (k)>>15; } \
else if (((k)&0x00008000) == 0) { (klevel) = 15; (kofs) = (k)>>16; } \
else if (((k)&0x00010000) == 0) { (klevel) = 16; (kofs) = (k)>>17; } \
else if (((k)&0x00020000) == 0) { (klevel) = 17; (kofs) = (k)>>18; } \
else if (((k)&0x00040000) == 0) { (klevel) = 18; (kofs) = (k)>>19; } \
else if (((k)&0x00080000) == 0) { (klevel) = 19; (kofs) = (k)>>20; } \
else if (((k)&0x00100000) == 0) { (klevel) = 20; (kofs) = (k)>>21; } \
else if (((k)&0x00200000) == 0) { (klevel) = 21; (kofs) = (k)>>22; } \
else if (((k)&0x00400000) == 0) { (klevel) = 22; (kofs) = (k)>>23; } \
else { (klevel) = 23; (kofs) = (k)>>24; }
*/


#define SL_HEAD(l) SL_LINK(SL_MAXLEVEL-1, 0, l)
#define SL_BHEAD(l) SL_BLINK(SL_MAXLEVEL-1, 0, l)
#define SL_HEADMIX SL_MIX(SL_MAXLEVEL-1, 0)

#define SL_CEIL4(x) (((x)+3)&~3)

/* average height is 1.5819767, this function starts with 3.1*n and converges to 1.6*n */
#define SL_EXPECTEDNUM(n) ((unsigned)(8*(UINT64)(n)*(UINT64)(193750+(n))/(5*(100000+(n)))))
#define SL_EXPECTEDSIZE(n) (((SL_HASBLINK)?2:1)*(1200+SL_EXPECTEDNUM(n))+(SL_KEYSIZE+SL_VALUESIZE)*((n)+100))

/* Table[Round[2^32*(1 - 1/E)/E^n], {n, 0, 22}], first item +1 */
static const unsigned SL_DIST[SL_MAXLEVEL] =
{2714937128, 998769553, 367426785, 135168760, 49725808, 18293102,
	6729656, 2475702, 910760, 335050, 123258, 45344, 16681, 6137, 2258,
831, 306, 112, 41, 15, 6, 2, 1};

static const unsigned SL_DISTSUM[SL_MAXLEVEL] =
{2714937128, 3713706681, 4081133466, 4216302226, 4266028034,
4284321136, 4291050792, 4293526494, 4294437254, 4294772304,
4294895562, 4294940906, 4294957587, 4294963724, 4294965982,
4294966813, 4294967119, 4294967231, 4294967272, 4294967287,
4294967293, 4294967295, 0};

SL_ATTR unsigned SL_PREFIX(head)(void)
{
	return SL_HEADMIX;
}

SL_ATTR unsigned SL_PREFIX(size)(unsigned num)
{
	return SL_EXPECTEDSIZE(num);
}

SL_ATTR void SL_PREFIX(clear)(SL_PREFIX(t) *pl)
{
	unsigned i, j;
	for (i = 0; i < SL_MAXLEVEL; i++) {
		if (pl->allocated[i] != 0) {
			unsigned last = (i == SL_MAXLEVEL-1 ? 1 : 0);
			for (j = last; j < pl->allocated[i]-1; j++) {
				SL_NEXTEMPTY(i, j) = j+1;
			}
			SL_NEXTEMPTY(i, pl->allocated[i]-1) = UNONE;
			pl->empty[i] = last;
		} else {
			pl->empty[i] = UNONE;
		}
		SL_HEAD(i) = SL_HEADMIX;
		#if SL_HASBLINK
		SL_BHEAD(i) = SL_HEADMIX;
		#endif
	}
	pl->usedlevel = 0;
	pl->num = 0;
}

/* size is number of unsigneds in buf */
SL_ATTR unsigned SL_PREFIX(init)(SL_PREFIX(t) *pl, unsigned *buf, unsigned size, void *callbackptr)
{
	unsigned i;
	for (i = 0; i < SL_MAXLEVEL; i++) {
		pl->itemsize[i] = SL_KEYSIZE + SL_VALUESIZE + i+1 + (SL_HASBLINK ? i+1 : 0);
		pl->links[i] = NULL;
	}
	if (buf != NULL) {
		unsigned itemsum = 0;
		UINT64 sum = 0;
		pl->isstatic = 1;
		for (i = 0; i < SL_MAXLEVEL; i++) {
			itemsum += pl->itemsize[i];
			sum += (UINT64)pl->itemsize[i]*(UINT64)SL_DIST[i];
		}
		if (size < 4*itemsum) {
			return UERROR;
		}
		size -= 4*itemsum;
		for (i = 0; i < SL_MAXLEVEL; i++) {
			pl->allocated[i] = 4+(unsigned)(((UINT64)SL_DIST[i]*(UINT64)size)/sum);
			pl->links[i] = buf;
			buf += pl->allocated[i]*pl->itemsize[i];
		}
	} else {
		unsigned *newptr;
		pl->callbackptr = callbackptr;
		pl->isstatic = 0;
		for (i = 0; i < SL_MAXLEVEL-1; i++) {
			pl->allocated[i] = 0;
		}
		pl->allocated[SL_MAXLEVEL-1] = 4;
		newptr = SL_REALLOC(pl->callbackptr, NULL, 4*pl->itemsize[SL_MAXLEVEL-1]*sizeof(unsigned));
		if (newptr == NULL) {
			return UERROR;
		}
		pl->links[SL_MAXLEVEL-1] = newptr;
	}
	SL_PREFIX(clear)(pl);
	return 0;
}

SL_ATTR void SL_PREFIX(exit)(SL_PREFIX(t) *pl)
{
	if (!pl->isstatic) {
		unsigned i;
		for (i = 0; i < SL_MAXLEVEL; i++) {
			if (pl->links[i] != NULL) SL_REALLOC(pl->callbackptr, pl->links[i], 0);
		}
	}
}

SL_ATTR unsigned SL_PREFIX(insert)(SL_PREFIX(t) *pl, unsigned *newkey, unsigned *newvalue, unsigned *found)
{
	unsigned i, l, ml, prevlevel = SL_MAXLEVEL-1, prevofs = 0, j, k, kmix, r;
	unsigned vprevlevel[SL_MAXLEVEL], vprevofs[SL_MAXLEVEL];
	ml = pl->usedlevel+1 < SL_MAXLEVEL-1 ? pl->usedlevel+1 : SL_MAXLEVEL-1; /* probably SL_MAXLEVEL-1 only */
	for (l = ml; l+1 != 0; l--) {
		for (i = SL_LINK(prevlevel, prevofs, l); i != SL_HEADMIX; i = SL_LINK(prevlevel, prevofs, l)) {
			int ret;
			unsigned ilevel, iofs;
			SL_SPLIT(i, ilevel, iofs);
			ret = SL_CMP(pl->callbackptr, SL_KEY(ilevel, iofs), newkey);
			if (ret == 0) {
				if (found) *found = 1;
				#if SL_VALUESIZE
				SL_VALUECPY(SL_VALUE(ilevel, iofs), newvalue, SL_VALUESIZE*sizeof(unsigned));
				#endif
				return i;
			}
			if (ret > 0) break;
			prevlevel = ilevel;
			prevofs = iofs;
		}
		vprevlevel[l] = prevlevel;
		vprevofs[l] = prevofs;
	}
	r = SL_RAND();
	for (l = 0; l < ml && r > SL_DISTSUM[l]; l++);
	if (pl->empty[l] == UNONE) {
		unsigned oldalloc;
		if (pl->isstatic) {
			return UERROR;
		}
		oldalloc = pl->allocated[l];
		pl->allocated[l] = SL_CEIL4((pl->allocated[l]+1)*3/2);
		pl->links[l] = SL_REALLOC(pl->callbackptr, pl->links[l], pl->allocated[l]*pl->itemsize[l]*sizeof(unsigned));
		if (pl->links[l] == NULL) {
			return UERROR;
		}
		for (i = oldalloc; i < pl->allocated[l]-1; i++) {
			SL_NEXTEMPTY(l, i) = i+1;
		}
		SL_NEXTEMPTY(l, pl->allocated[l]-1) = UNONE;
		pl->empty[l] = oldalloc;
	}
	if (l > pl->usedlevel) pl->usedlevel = l;
	k = pl->empty[l];
	pl->empty[l] = SL_NEXTEMPTY(l, k);
	kmix = SL_MIX(l, k);
	SL_KEYCPY(SL_KEY(l, k), newkey, SL_KEYSIZE*sizeof(unsigned));
	#if SL_VALUESIZE
	SL_VALUECPY(SL_VALUE(l, k), newvalue, SL_VALUESIZE*sizeof(unsigned));
	#endif
	pl->num++;
	for (j = l; j+1 != 0; j--) {
		SL_LINK(l, k, j) = SL_LINK(vprevlevel[j], vprevofs[j], j);
		SL_LINK(vprevlevel[j], vprevofs[j], j) = kmix;
		#if SL_HASBLINK
		{
			unsigned xlevel, xofs;
			SL_BLINK(l, k, j) = SL_MIX(vprevlevel[j], vprevofs[j]);
			SL_SPLIT(SL_LINK(l, k, j), xlevel, xofs);
			SL_BLINK(xlevel, xofs, j) = kmix;
		}
		#endif
	}
	if (found) *found = 0;
	return kmix;
}

SL_STATICATTR unsigned SL_PREFIX(searchinner)(SL_PREFIX(t) *pl, void *searchkey, unsigned *found, unsigned *plevel, unsigned *pofs)
{
	unsigned i, l, prevlevel = SL_MAXLEVEL-1, prevofs = 0;
	for (l = pl->usedlevel; l+1 != 0; l--) {
		for (i = SL_LINK(prevlevel, prevofs, l); i != SL_HEADMIX; i = SL_LINK(prevlevel, prevofs, l)) {
			int ret;
			unsigned ilevel, iofs;
			SL_SPLIT(i, ilevel, iofs);
			ret = SL_CMP(pl->callbackptr, SL_KEY(ilevel, iofs), searchkey);
			if (ret == 0) {
				if (found) *found = 1;
				return i;
			}
			if (ret > 0) break;
			prevlevel = ilevel;
			prevofs = iofs;
		}
	}
	if (found) *found = 0;
	if (plevel) *plevel = prevlevel;
	if (pofs) *pofs = prevofs;
	return UNOTFOUND;
}

SL_ATTR unsigned SL_PREFIX(search)(SL_PREFIX(t) *pl, void *searchkey)
{
	return SL_PREFIX(searchinner)(pl, searchkey, NULL, NULL, NULL);
}

SL_ATTR unsigned SL_PREFIX(psearch)(SL_PREFIX(t) *pl, void *searchkey, unsigned *found)
{
	unsigned ret, prevlevel, prevofs;
	ret = SL_PREFIX(searchinner)(pl, searchkey, found, &prevlevel, &prevofs);
	if (ret != UNOTFOUND) return ret;
	ret = SL_MIX(prevlevel, prevofs);
	return ret == SL_HEADMIX ? UNOTFOUND : ret;
}

SL_ATTR unsigned SL_PREFIX(nsearch)(SL_PREFIX(t) *pl, void *searchkey, unsigned *found)
{
	unsigned ret, prevlevel = 0, prevofs = 0;
	ret = SL_PREFIX(searchinner)(pl, searchkey, found, &prevlevel, &prevofs);
	if (ret != UNOTFOUND) return ret;
	ret = SL_LINK(prevlevel, prevofs, 0);
	return ret == SL_HEADMIX ? UNOTFOUND : ret;
}

SL_ATTR void SL_PREFIX(delete)(SL_PREFIX(t) *pl, unsigned k, unsigned *found)
{
	unsigned i, ilevel, iofs, l, prevlevel = SL_MAXLEVEL-1, prevofs = 0, klevel, kofs, ifound = 0;
	SL_SPLIT(k, klevel, kofs);
	for (l = pl->usedlevel; l+1 != 0; l--) {
		for (i = SL_LINK(prevlevel, prevofs, l); i != SL_HEADMIX; i = SL_LINK(prevlevel, prevofs, l)) {
			SL_SPLIT(i, ilevel, iofs);
			if (SL_CMP(pl->callbackptr, SL_KEY(ilevel, iofs), SL_KEY(klevel, kofs)) >= 0) break;
			prevlevel = ilevel;
			prevofs = iofs;
		}
		if (i == k) {
			ifound = 1;
			SL_LINK(prevlevel, prevofs, l) = SL_LINK(klevel, kofs, l);
			#if SL_HASBLINK
			{
				unsigned xlevel, xofs;
				SL_SPLIT(SL_LINK(prevlevel, prevofs, l), xlevel, xofs);
				SL_BLINK(xlevel, xofs, l) = SL_MIX(prevlevel, prevofs);
			}
			#endif
		}
	}
	if (ifound) {
		SL_NEXTEMPTY(klevel, kofs) = pl->empty[klevel];
		pl->empty[klevel] = kofs;
		while (pl->usedlevel > 0 && SL_HEAD(pl->usedlevel) == SL_HEADMIX) pl->usedlevel--;
		pl->num--;
	}
	if (found) *found = ifound;
}

/* returns first if k = SL_PREFIX(head)*/
SL_ATTR unsigned SL_PREFIX(next)(SL_PREFIX(t) *pl, unsigned k)
{
	unsigned ret, level, ofs;
	SL_SPLIT(k, level, ofs);
	ret = SL_LINK(level, ofs, 0);
	if (ret == SL_HEADMIX) return UNOTFOUND;
	return ret;
}

/* returns last if k = SL_PREFIX(head)*/
SL_ATTR unsigned SL_PREFIX(prev)(SL_PREFIX(t) *pl, unsigned k)
{
	unsigned klevel, kofs;
	SL_SPLIT(k, klevel, kofs);
	#if SL_HASBLINK
	{
		unsigned ret;
		ret = SL_BLINK(klevel, kofs, 0);
		return ret == SL_HEADMIX ? UNOTFOUND : ret;
	}
	#else
	{
		unsigned prevlevel = SL_MAXLEVEL-1, prevofs = 0, ret;
		if (k == SL_HEADMIX) {
			unsigned i, l;
			for (l = pl->usedlevel; l+1 != 0; l--) {
				for (i = SL_LINK(prevlevel, prevofs, l); i != SL_HEADMIX; i = SL_LINK(prevlevel, prevofs, l)) {
					SL_SPLIT(i, prevlevel, prevofs);
				}
			}
		} else {
			unsigned i, l, *kkey;
			kkey = SL_KEY(klevel, kofs);
			for (l = pl->usedlevel; l+1 != 0; l--) {
				for (i = SL_LINK(prevlevel, prevofs, l); i != SL_HEADMIX; i = SL_LINK(prevlevel, prevofs, l)) {
					int ret;
					unsigned ilevel, iofs;
					SL_SPLIT(i, ilevel, iofs);
					ret = SL_CMP(pl->callbackptr, SL_KEY(ilevel, iofs), kkey);
					if (ret >= 0) break;
					prevlevel = ilevel;
					prevofs = iofs;
				}
			}
		}
		ret = SL_MIX(prevlevel, prevofs);
		return ret == SL_HEADMIX ? UNOTFOUND : ret;
	}
	#endif
}

SL_ATTR unsigned *SL_PREFIX(getkey)(SL_PREFIX(t) *pl, unsigned k)
{
	unsigned level, ofs;
	SL_SPLIT(k, level, ofs);
	return SL_KEY(level, ofs);
}

SL_ATTR unsigned *SL_PREFIX(getvalue)(SL_PREFIX(t) *pl, unsigned k)
{
	unsigned level, ofs;
	SL_SPLIT(k, level, ofs);
	return SL_VALUE(level, ofs);
}

SL_ATTR unsigned SL_PREFIX(num)(SL_PREFIX(t) *pl)
{
	return pl->num;
}

#ifdef SL_PRINT
SL_ATTR void SL_PREFIX(print)(SL_PREFIX(t) *pl)
{
	unsigned i, j, k, klevel, kofs, alloc = 0;
	unsigned *v, vsmall[110];

	if (pl->num <= 100) v = vsmall;
	else {
		alloc = 1;
		v = malloc((pl->num+10)*sizeof(unsigned));
	}

	klevel = SL_MAXLEVEL-1;
	kofs = 0;
	for (v[0] = SL_LINK(klevel, kofs, 0), i = 0; v[i] != SL_HEADMIX; v[++i] = SL_LINK(klevel, kofs, 0)) {
		SL_SPLIT(v[i], klevel, kofs);
	}

	printf("num:%u, usedlevel:%u\n", pl->num, pl->usedlevel);
	for (i = pl->usedlevel; i+1 != 0; i--) {
		printf("x");
		for (j = 0, k = SL_HEAD(i); k != SL_HEADMIX; k = SL_LINK(klevel, kofs, i), j++) {
			SL_SPLIT(k, klevel, kofs);
			for (; v[j] != k; j++) printf("----");
			printf("---|");
		}
		for (; v[j] != SL_HEADMIX; j++) printf("----");
		printf("---x\n");
	}
	if (alloc) free(v);
}
#endif

///
