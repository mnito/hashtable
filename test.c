#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "hashtable.h"

#define MIN_TABLE_SIZE 1
#define MAX_TABLE_SIZE 65000
#define MAX_INPUT 255
#define MAX_KEY 100
#define MAX_VALUE 154

static bool haspre(char *prefix, char *str)
{
    char *test = strstr(str, prefix);
    return test == str;
}

static bool command(char *command, char *data)
{
	return haspre(command, data);
}

static bool put(char *input, HASHTABLE ht)
{
     		char *key;
		char *value;
		key = (char*)malloc(sizeof(char) * MAX_KEY);
		value = (char*)malloc(sizeof(char) * MAX_VALUE);
		if(sscanf(input, "put %s %[^\n]", key, value) < 2) {
			return 0;
		}
		hashtable_put(key, value, ht);
		free(key);
		free(value);
		puts("Put.");
		return 1;
}

static bool get(char *input, HASHTABLE ht)
{
		char *key;
		key = (char*)malloc(sizeof(char) * MAX_KEY);
		if(sscanf(input, "get %s", key) < 1) {
			return 0;
		}
		char *value = hashtable_getv(key, ht);
		if(strcmp(value, "") == 0) {
			puts("Entry does not exist.");
		} else {
                        printf("Got: %s\n", value);
		}
		free(key);
		return 1;
}

static bool _remove(char *input, HASHTABLE ht)
{
		char *key;
		key = (char*)malloc(sizeof(char) * MAX_KEY);
		if(sscanf(input, "remove %s", key) < 1) {
			return 0;
		}
		hashtable_remove(key, ht);
		printf("Removed: %s\n", key);
		free(key);
		return 1;
}

static bool print(char *input, HASHTABLE ht)
{
	char *all = (char*)malloc(sizeof(char) * 4);
	if(sscanf(input, "print %s", all) >= 1) {
			hashtable_print(ht, 1);
			return 1;
		
	}
	hashtable_print(ht, 0);
	return 1;
}

bool process(char *input, HASHTABLE ht)
{
	if(command("quit", input)) {
                hashtable_deinit(&ht);
		exit(0);
		return 1;
	}
	if(command("help", input)) {
		puts("Commands:");
		puts("put <key> <value>");
		puts("get <key>");
		puts("remove <key>");
		puts("print");
		puts("print all");
		puts("help");
		puts("quit");
		return 1;
	}
	if(command("put", input)) {
		return put(input, ht);
	}
	if(command("get", input)) {
		return get(input, ht);
	}
	if(command("remove", input)) {
		return _remove(input, ht);		
	}
	if(command("print", input)) {
		return print(input, ht);
	}
        return 0;
}

int main(int argc, char **argv)
{
	long int size;
	if(argc < 2 ) {
		puts("Usage: hashtable_cli <int>");
		return 0;
	}
	size = strtol(argv[1], NULL, 10);
	if(size < MIN_TABLE_SIZE || size > MAX_TABLE_SIZE) {
		printf("Hashtable size must be between %d and %d", MIN_TABLE_SIZE, MAX_TABLE_SIZE);
		return 0;
	}
	HASHTABLE ht = hashtable_init(size);
	puts("Simple Hashtable Test");
	char input[MAX_INPUT];
	while(1) {
		printf(" hashtable>");
		fgets(input, MAX_INPUT, stdin);
		if(!(process(input, ht))) {
			puts("Invalid input. Type help for commands.");
		}
	}
        return 0;
}
