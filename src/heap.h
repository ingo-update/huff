#ifndef _HEAP_H_
#define _HEAP_H_

#ifdef CUSTOM_HEAP_ELEMENT
#include "heap_element.h"
#else
#define heap_element int
#define heap_order(x,y) ((x) > (y))
#endif /* CUSTOM_HEAP_ELEMENT */

#define left(x) (2*x)+1
#define right(x) (2*x)+2
#define parent(x) ((x-1)/2)

typedef struct heap_t *heap;
struct heap_t
{
  heap_element *array;
  int size;
};

heap build_heap(heap_element *a, int s);
void heap_sort(heap_element *a, int s);

int heap_size(heap h);
void heap_insert(heap h, heap_element e);
heap_element heap_extract(heap h);

#endif /* _HEAP_H_ */
