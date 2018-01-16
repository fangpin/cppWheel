/* quadratic probing */
/* move foward when confilict until meet an empty cell. */
/* move i*i step long at i step. */
/* when tableSize is prime and tableSize > 2* numberOfElements, insert will always be supported. */
#ifndef _OPEN_ADREDSSING_H
#define _OPEN_ADREDSSING_H


typedef int Element;
enum KindeOfCell {Legitimate, Empty, Deleted};

typedef struct Entry
{
    Element element;
    enum KindOfCell type;
}Entry;

typedef Entry* Cell;
typedef Entry* Position;

typedef struct
{
    int tableSize;
    Cell table;
}HashTable;

typedef HashTable* HashTbl;


HashTbl init(unsigned int tableSize);
Position find(HashTbl tbl, Element x);
void insert(HashTbl tbl, Element x);

/* set mark for lazy delete and really do it when rehashing */
#endif
