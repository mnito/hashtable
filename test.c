#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

#define MAX_INPUT 256
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

int main(int argc, char** argv)
{
	HASHTABLE ht = hashtable_init(1024);
	char input[MAX_INPUT];
	while(1) {
		printf(" hashtable>");
		fgets(input, MAX_INPUT, stdin);
	}
	char *quit;
	quit = strstr(input, "quit");
	if(quit == input) {
		exit(0);
	}
	char *put;
	put = strstr(input, "put");
	if(put == input) {
		printf("put command");
	}
	char *get;
	get = strstr(input, "get");
	if(get == input) {
		printf("get command");
	}
}
