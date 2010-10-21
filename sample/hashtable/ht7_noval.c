// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

#include <stdlib.h>
#include <assert.h>
#include "ht7_noval.h"

#define HTMINSIZE 8
#define HTMAXSIZE (1U << 31)

static inline unsigned int entryhash(const Htentry *entry) {
	return entry->hash;
}

static inline unsigned int keyhash(Ht *ht, Htkey k) {
	/* mark used */
	return ht->keyhash(ht->param, k) | HTMAXSIZE;
}

static void htinit(Ht *ht, unsigned int (*keyhash)(void *, Htkey), int (*keyeq)(void *, Htkey, Htkey), void *param) {
	ht->mask = HTMINSIZE - 1;
	ht->used = 0;
	ht->table = calloc(ht->mask + 1, sizeof(Htentry));
	assert(ht->table);
	ht->keyhash = keyhash;
	ht->keyeq = keyeq;
	ht->param = param;
}

static void htuninit(Ht *ht) {
	free(ht->table);
	ht->table = NULL;
}

Ht *htalloc(unsigned int (*keyhash)(void *, Htkey), int (*keyeq)(void *, Htkey, Htkey), void *param) {
	Ht *ht = malloc(sizeof(Ht));

	assert(ht);
	htinit(ht, keyhash, keyeq, param);
	return ht;
}

void htclear(Ht *ht) {
	htuninit(ht);
	htinit(ht, ht->keyhash, ht->keyeq, ht->param);
}

void htfree(Ht *ht) {
	htuninit(ht);
	free(ht);
}

/* one lookup function to rule them all */
static Htentry *lookup(Ht *ht, Htkey key, unsigned int hash) {
	unsigned int mask = ht->mask;
	unsigned int i = hash;
	Htentry *table = ht->table;
	Htentry *entry = table + (i & mask);

	if (htisempty(entry))
		return entry;
	else if (entryhash(entry) == hash && ht->keyeq(ht->param, entry->key, key))
		return entry;
	for (i++;; i++) {
		entry = table + (i & mask);
		if (htisempty(entry) ||
		   (entryhash(entry) == hash && ht->keyeq(ht->param, entry->key, key)))
			return entry;
	}
}

/* for copy and resize: entry->key is not in ht */
static void cleaninsert(Ht *ht, const Htentry *entry) {
	unsigned int mask = ht->mask;
	unsigned int i = entryhash(entry);
	Htentry *table = ht->table;
	Htentry *newentry = table + (i & mask);

	if (!htisempty(newentry))
		for (i++; !htisempty(newentry); i++)
			newentry = table + (i & mask);
	ht->used++;
	*newentry = *entry;
}

Ht *htcopy(const Ht *ht) {
	Ht *newht;
	Htentry *entry;
	unsigned int used;

	newht = calloc(1, sizeof(Ht));
	assert(newht);
	newht->mask = ht->mask;
	newht->table = calloc(newht->mask + 1, sizeof(Htentry));
	assert(newht->table);
	for (entry = ht->table, used = ht->used; used > 0; entry++)
		if (htisused(entry)) {
			used--;
			cleaninsert(newht, entry);
		}
	return newht;
}

void htresize(Ht *ht, unsigned int hint) {
	unsigned int newsize;
	unsigned int oldused = ht->used;
	Htentry *oldtable = ht->table;
	Htentry *entry;

	/* TODO: oldused + (oldused >> 1) */
	if (hint < oldused << 1)
		hint = oldused << 1;
	if (hint > HTMAXSIZE)
		hint = HTMAXSIZE;
	for (newsize = HTMINSIZE; newsize < hint; newsize <<= 1);
	ht->table = calloc(newsize, sizeof(Htentry));
	assert(ht->table);
	ht->mask = newsize - 1;
	ht->used = 0;
	for (entry = oldtable; oldused > 0; entry++)
		if (htisused(entry)) {
			oldused--;
			cleaninsert(ht, entry);
		}
	free(oldtable);
}

int hthas(Ht *ht, Htkey key) {
	Htentry *entry = lookup(ht, key, keyhash(ht, key));

	return htisused(entry);
}

Htentry *htgetentry(Ht *ht, Htkey key) {
	Htentry *entry = lookup(ht, key, keyhash(ht, key));

	return htisused(entry) ? entry : NULL;
}

/* fill threshold = 3/4 */
static inline void checkfill(Ht *ht) {
//	if (ht->used > ht->mask - (ht->mask >> 2))
	if (ht->used > (ht->mask >> 1))
		htresize(ht, ht->used << (ht->used > 1 << 16 ? 1 : 2));
}

Htentry *htinsert(Ht *ht, Htkey key) {
	unsigned int hash = keyhash(ht, key);
	Htentry *entry = lookup(ht, key, hash);

	if (htisused(entry))
		return entry;
	ht->used++;
	entry->hash = hash;
	entry->key = key;
	checkfill(ht);
	return NULL;
}

///
