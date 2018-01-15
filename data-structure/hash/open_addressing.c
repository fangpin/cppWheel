/* quadratic probing */
/* move foward when confilict until meet an empty cell. */
/* move i*i step long at i step. */
/* when tableSize is prime and tableSize > 2* numberOfElements, insert will always be supported. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "open_addressing.h"


static int
_is_prime(int x)
{
    int i;
    for(i=2; i<=(int)sqrt(x); ++i)
    {
        if(x % i == 0)
            return 0;
    }
    return 1;
}


static int
_next_prime(int x)
{
    while(1)
    {
        if(_is_prime(x++))
            return x-1;
    }
}


HashTbl
init(unsigned int tableSize)
{
    HashTbl tbl = (HashTbl)malloc(sizeof(HashTable));
    if(!tbl)
    {
        fprintf(stderr, "malloc error.\n");
        exit(1);
    }
    tbl->tableSize = _next_prime(tableSize);
    tbl->table = (Cell)malloc(tbl->tableSize * sizeof(Entry));
    if(!tbl->table)
    {
        fprintf(stderr, "malloc error.\n");
        exit(1);
    }
    return tbl;
}


static inline int
hash(int x, int mod)
{
    return x % mod;
}


Position
find(HashTbl tbl, Element x)
{
    int pos = hash(x, tbl->tableSize);
    int num = 0;
    while(tbl->table[pos].type != Empty && tbl->table[pos].element != x)
    {
        pos += 2 * (++num) - 1;
        if(pos >= tbl->tableSize)
            pos -= tbl->tableSize;
    }
    return tbl->table + pos;
}


void
insert(HashTbl tbl, Element x)
{
    Position pos = find(tbl, x);
    if(pos->type != Legitimate)
    {
        pos->type = Legitimate;
        pos->element = x;
    }
}
