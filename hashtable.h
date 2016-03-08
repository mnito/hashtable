#ifndef HASHTABLE_H
#define HASHTABLE_H

struct Hashtable_Entry
{
	char *key;
	char *value;
	unsigned long hash;
};

struct Hashtable
{
	int size;
	int *count;
	struct Hashtable_Entry* table;
};

typedef struct Hashtable_Entry HASHTABLE_ENTRY;
typedef struct Hashtable HASHTABLE;

HASHTABLE hashtable_init(int size);

unsigned long hashtable_hash(char *str);

int hashtable_probe(int ht_key, char* key, HASHTABLE ht);

_Bool hashtable_put(char *key, char *value, HASHTABLE ht);

HASHTABLE_ENTRY hashtable_get(char *key, HASHTABLE ht);

char* hashtable_getv(char* key, HASHTABLE ht);

_Bool hashtable_exists(char *key, HASHTABLE ht);

_Bool hashtable_remove(char* key, HASHTABLE ht);

void hashtable_deinit(HASHTABLE *ht);

#endif
