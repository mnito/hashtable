#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *strdup(const char *str)
{
    char *dup;
    size_t length = strlen(str) + 1;
    if((dup = malloc(length)) == NULL) {
        memcpy(dup, str, length);
    }
    return dup;
}
