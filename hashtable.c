#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "djb2.h"
#include "hashtable.h"

HASHTABLE hashtable_init(int size)
{
	HASHTABLE ht;
	int i;
	ht.size = size;
	ht.count = (int*)malloc(sizeof(int));
	*(ht.count) = 0;
	ht.table = (HASHTABLE_ENTRY*)malloc(sizeof(HASHTABLE_ENTRY) * size);
	for(i = 0; i < size; i++) {
		HASHTABLE_ENTRY entry;
		entry.value = "";
		entry.key = "";
		entry.hash = -1;
		ht.table[i] = entry;
	}
	return ht;
}

unsigned long hashtable_hash(char *str)
{
	return djb2(str);
}

int hashtable_probe(int ht_key, char *key, HASHTABLE ht)
{
	if(strcmp(ht.table[ht_key].key, "") && strcmp(ht.table[ht_key].key, key)) {
		ht_key = (ht_key + 1) % ht.size;
		while(strcmp(ht.table[ht_key].key, "")
		&& strcmp(ht.table[ht_key].key, key)) {
			ht_key = (ht_key + 1) % ht.size;
		}
	}
	return ht_key;
}

bool hashtable_put(char *key, char *value, HASHTABLE ht)
{
	if(*(ht.count) >= ht.size) {
		return 0;
	}
	HASHTABLE_ENTRY entry;
	unsigned long hash;
	int ht_key;
	hash = hashtable_hash(key);
	entry.key = strdup(key);
	entry.value = strdup(value);
	ht_key = hashtable_probe(hash % ht.size, key, ht);
	entry.hash = ht_key;
	ht.table[ht_key] = entry;
	*(ht.count) = *(ht.count) + 1;
	return 1;
}

HASHTABLE_ENTRY hashtable_get(char *key, HASHTABLE ht)
{
	unsigned long hash;
	int ht_key;
	HASHTABLE_ENTRY entry;
	hash = hashtable_hash(key);
	ht_key = hashtable_probe(hash % ht.size, key, ht);
	return ht.table[ht_key];
}

char* hashtable_getv(char *key, HASHTABLE ht)
{
	return hashtable_get(key, ht).value;
}

bool hashtable_exists(char *key, HASHTABLE ht)
{
	return hashtable_get(key, ht).hash != -1;
}

bool hashtable_remove(char *key, HASHTABLE ht)
{
	HASHTABLE_ENTRY entry = hashtable_get(key, ht);
	if(entry.hash == -1) {
		return 0;
	}
	int hash = entry.hash;
	entry.hash = -1;
	entry.value = "";
	entry.key = "";
	ht.table[hash] = entry;
}

void hashtable_deinit(HASHTABLE *ht)
{
	free(ht->count);
	ht->count = NULL;
	free(ht->table);
	ht->table = NULL;
}
