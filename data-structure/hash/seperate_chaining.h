#ifndef _SEPARATE_CHAINING_H
#define _SEPARATE_CHAINING_H

struct LinkedList;
typedef struct LinkedList* Position;
typedef int Element;

struct LinkedList
{
    Element element;
    Position next;
};

typedef struct HashTable
{
    int tableSize;
    Position* list;
}HashTable;

typedef HashTable* HashTbl;

HashTbl init_table(unsigned int tableSize);
Position find(HashTbl tbl, Element x);
void insert(HashTbl tbl, Element x);
void delete(HashTbl tbl, Element x);


#endif
