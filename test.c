#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

#define MAX_INPUT 255
#define MAX_KEY 100
#define MAX_VALUE 154

int haspre(char *prefix, char *str)
{
    char *test = strstr(str, prefix);
    return test == str;
}

int process(char* input, HASHTABLE ht)
{
	char *quit;
	quit = strstr(input, "quit");
	if(quit == input) {
		exit(0);
	}
	char *put;
	put = strstr(input, "put");
	if(put == input) {
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
	}
	char *get;
	get = strstr(input, "get");
	if(get == input) {
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
	}
	char *remove;
	remove = strstr(input, "remove");
	if(remove == input) {
		char *key;
		key = (char*)malloc(sizeof(char) * MAX_KEY);
		if(sscanf(input, "remove %s", key) < 1) {
			return 0;
		}
		hashtable_remove(key, ht);
		printf("Removed: %s\n", key);
		free(key);
	}
        return 1;
}

int main(int argc, char **argv)
{
	HASHTABLE ht = hashtable_init(1024);
	puts("Simple Hashtable Test");
	char input[MAX_INPUT];
	while(1) {
		printf(" hashtable>");
		fgets(input, MAX_INPUT, stdin);
		process(input, ht);
	}
        return 0;
}
