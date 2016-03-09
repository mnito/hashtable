#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "djb2.h"
#include "hashtable.h"

static HASHTABLE hashtable_fill(int size, HASHTABLE ht)
{
	int i;
	for(i = 0; i < size; i++) {
		HASHTABLE_ENTRY entry;
		entry.value = "";
		entry.key = "";
		entry.hash = -1;
		ht.table[i] = entry;
	}
	return ht;	
}

HASHTABLE hashtable_init(int size)
{
	HASHTABLE ht;
	ht.size = size;
	ht.count = (int*)malloc(sizeof(int));
	*(ht.count) = 0;
	ht.table = (HASHTABLE_ENTRY*)malloc(sizeof(HASHTABLE_ENTRY) * size);
	return hashtable_fill(size, ht);
}


unsigned long hashtable_hash(char *str)
{
	return djb2((unsigned char*)str);
}

static int hashtable_probe(int ht_key, char *key, HASHTABLE ht)
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

HASHTABLE_ENTRY hashtable_get(char *key, HASHTABLE ht)
{
	unsigned long hash;
	int ht_key;
	hash = hashtable_hash(key);
	ht_key = hashtable_probe(hash % ht.size, key, ht);
	return ht.table[ht_key];
}

bool hashtable_exists(char *key, HASHTABLE ht)
{
	return hashtable_get(key, ht).hash != -1;
}

bool hashtable_put(char *key, char *value, HASHTABLE ht)
{
	if(*(ht.count) >= ht.size -1) return 0;
	HASHTABLE_ENTRY entry;
	unsigned long hash;
	int ht_key;
	hash = hashtable_hash(key);
	entry.key = strdup(key);
	entry.value = strdup(value);
	ht_key = hashtable_probe(hash % ht.size, key, ht);
	entry.hash = ht_key;
	if(ht.table[ht_key].hash == -1) *(ht.count) = *(ht.count) + 1;
	ht.table[ht_key] = entry;
	return 1;
}

char *hashtable_getv(char *key, HASHTABLE ht)
{
	return hashtable_get(key, ht).value;
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
        return 1;
}

void hashtable_deinit(HASHTABLE *ht)
{
	free(ht->count);
	ht->count = NULL;
	free(ht->table);
	ht->table = NULL;
}

void hashtable_print(HASHTABLE ht, bool all)
{
	int i;
	for(i = 0; i < ht.size; i++) {
		HASHTABLE_ENTRY entry = ht.table[i];
		if(all < 1) {
		     	if(entry.hash == -1) {
				continue;
			}
		}
		printf("%d : %s : %s\n", entry.hash, entry.key, entry.value);
	}
}
