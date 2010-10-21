// BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

/* open addressing hash table: ui -> ui, use type cast for other types */
/* no malloc checks (out of memory == segfault), max size is 1 << 31 */
/* an entry pointer is valid until the next insertion or resize */

typedef unsigned Htkey;

typedef struct {
	unsigned int hash;
	Htkey key;
} Htentry;

typedef struct {
	unsigned int mask;
	unsigned int used;
	Htentry *table;

	unsigned int (*keyhash)(void *, Htkey);
	int (*keyeq)(void *, Htkey, Htkey);
	void *param;
} Ht;

Ht *htalloc(unsigned int (*keyhash)(void *, Htkey), int (*keyeq)(void *, Htkey, Htkey), void *param);
void htfree(Ht *ht);
void htclear(Ht *ht);
Ht *htcopy(const Ht *ht);
/* new size is 2^n >= hint */
void htresize(Ht *ht, unsigned int hint);

/* ht[key] is used */
int hthas(Ht *ht, Htkey key);
/* entry of ht[key] or NULL if key is not used */
Htentry *htgetentry(Ht *ht, Htkey key);
/* if key is used then return ht[key] else ht[key] = value and return NULL */
/* (the value of the returned used entry can be modified) */
Htentry *htinsert(Ht *ht, Htkey key);

/* helper functions */
static inline unsigned int htlen(const Ht *ht) {return ht->used;}
static inline unsigned int htsize(const Ht *ht) {return ht->mask + 1;}

/* for any entry exactly one returns true */
static inline int htisused(const Htentry *entry) {return (entry->hash & 0x80000000) != 0;}
static inline int htisempty(const Htentry *entry) {return (entry->hash & 0x80000000) == 0;}

/* first used (useful for iteration) */
static inline Htentry *htfirst(const Ht *ht) {
	Htentry *entry = 0;

	if (ht->used)
		for (entry = ht->table; !htisused(entry); entry++);
	return entry;
}

/* next used (useful for iteration) */
static inline Htentry *htnext(const Ht *ht, Htentry *entry) {
	while (++entry != ht->table + ht->mask + 1)
		if (htisused(entry))
			return entry;
	return 0;
}

///
