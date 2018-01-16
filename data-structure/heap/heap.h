/* min root heap */
#ifndef _HEAP_h
#define _HEAP_h

typedef int Element;

typedef struct Heap
{
    int capacity;
    int size;
    Element *data;
}Heap;

Heap *init(int capacity);
void insert(Heap *heap, Element x);
Element delete(Heap *heap);
Element get_root(Heap *heap);
int is_full(Heap *heap);
int is_empty(Heap *heap);
void destroy(Heap *heap);


#endif
