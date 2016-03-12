#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct Hashtable_Entry
{
    char *key;
    char *value;
    int hash;
} HASHTABLE_ENTRY;

typedef struct
{
    int size;
    int *count;
    struct Hashtable_Entry *table;
} HASHTABLE;

HASHTABLE hashtable_init(int size);

unsigned long hashtable_hash(char *str);

_Bool hashtable_put(char *key, char *value, HASHTABLE ht);

HASHTABLE_ENTRY hashtable_get(char *key, HASHTABLE ht);

char *hashtable_getv(char *key, HASHTABLE ht);

_Bool hashtable_exists(char *key, HASHTABLE ht);

_Bool hashtable_remove(char *key, HASHTABLE ht);

void hashtable_deinit(HASHTABLE *ht);

void hashtable_print(HASHTABLE ht, _Bool all);

void hashtable_resize(int size, HASHTABLE *ht);

#endif
