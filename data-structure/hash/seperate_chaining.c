#include <stdio.h>
#include <stdlib.h>
#include "seperate_chaining.h"


HashTbl
init_table(unsigned int tableSize)
{
    int i;
    HashTbl h = (HashTbl)malloc(sizeof(HashTable));
    if(!h)
    {
        fprintf(stderr, "malloc error.\n");
        exit(1);
    }
    h->tableSize = tableSize;
    h->list = (Position*)malloc(tableSize * sizeof(Position));
    for (i=0; i<(int)tableSize; ++i)
        h->list[i] = NULL;
    return h;
}


static inline unsigned int
hash(Element key, int tableSize)
{
    return key % tableSize;
}


Position
find(HashTbl tbl, Element x)
{
    Position pos = tbl->list[hash(x, tbl->tableSize)]->next;
    while(pos && pos->element != x)
        pos = pos->next;
    return pos;
}


void
insert(HashTbl tbl, Element x)
{
    if(!find(tbl, x))
    {
        struct LinkedList* node = (struct LinkedList*)malloc(sizeof(struct LinkedList));
        if(!node)
        {
            fprintf(stderr, "malloc error.\n");
            exit(1);
        }
        node->element = x;
        Position pos = tbl->list[hash(x, tbl->tableSize)];
        node->next = pos->next;
        pos->next = node;
    }
}


void
delete(HashTbl tbl, Element x)
{
    Position pre = tbl->list[hash(x, tbl->tableSize)];
    Position pos = pre->next;
    while(pos && pos->element != x)
    {
        pre = pos;
        pos = pos->next;
    }
    if(pos)
    {
        pre->next = pos->next;
        free(pos);
    }
}
