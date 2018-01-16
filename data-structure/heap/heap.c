#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

Heap *
init(int capacity)
{
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    if(!heap)
    {
        fprintf(stderr, "malloc error.\n");
        exit(1);
    }
    heap->capacity = capacity;
    heap->size = 0;
    heap->data = (Element *)malloc((capacity+1) * sizeof(Element));
    if(!heap->data)
    {
        fprintf(stderr, "malloc error.\n");
        exit(1);
    }
    return heap;
}

int
is_full(Heap *heap)
{
    return heap->size == heap->capacity;
}

int
is_empty(Heap *heap)
{
    return heap->size == 0;
}

void
destroy(Heap *heap)
{
    free(heap->data);
    free(heap);
    heap->data = NULL;
    heap = NULL;
}

Element
get_root(Heap *heap)
{
    if(is_empty(heap))
    {
        fprintf(stderr, "heap is empty.\n");
        exit(1);
    }
    return heap->data[1];
}

void insert(Heap *heap, Element x)
{
    if(is_full(heap))
    {
        fprintf(stderr, "heap is full.\n");
        exit(1);
    }
    int i;
    /* heap->data[++heap->size] = x; */
    for(i=++heap->size; i>0 && heap->data[i]; i=i/2)
        heap->data[i] = heap->data[i/2];
    heap->data[i] = x;
}

Element
delete(Heap *heap)
{
    if(is_empty(heap))
    {
        fprintf(stderr, "heap is empty.\n");
        exit(1);
    }
    Element root = heap->data[1];
    Element last = heap->data[heap->size--];
    int i, child;
    for(i=1; i*2 <= heap->size; i=child)
    {
        child = i*2;
        if(child + 1 <= heap->size && heap->data[child] > heap->data[child+1])
            ++child;
        if(last < heap->data[child])
            break;
        else
            heap->data[i] = heap->data[child];
    }
    heap->data[i] = last;
    return root;
}
