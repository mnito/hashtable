#include "hash.h"

//djb2 hashing function - author Daniel J. Bernstein
unsigned long djb2(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

unsigned long hash(unsigned char *str)
{
    return djb2(str);
}
