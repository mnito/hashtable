#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

#define MAX_INPUT 255
#define MAX_KEY 100
#define MAX_VALUE 154
/*
int main(int argc, char** argv)
{
	HASHTABLE ht = hashtable_init(1024);
	hashtable_put("foo", "bar", ht);
	hashtable_put("baz", "qux", ht);
	puts(hashtable_getv("foo", ht));
	puts(hashtable_getv("baz", ht));
	printf("%d", hashtable_exists("baz", ht));
	hashtable_remove("baz", ht);
	printf("%d", hashtable_exists("baz", ht));
	puts(hashtable_getv("baz", ht));
	hashtable_deinit(&ht);
	return 0;
}
*/

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
		printf("Got: %s\n", hashtable_getv(key, ht));
		free(key);
	}
	char *remove;
	remove = strstr(input, "remove");
	if(remove == input) {
		printf("remove command");
	}
}

int main(int argc, char** argv)
{
	HASHTABLE ht = hashtable_init(1024);
	puts("Simple Hashtable Test");
	char input[MAX_INPUT];
	while(1) {
		printf(" hashtable>");
		fgets(input, MAX_INPUT, stdin);
		process(input, ht);
	}

}
