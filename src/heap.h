#ifndef _HEAP_H_
#define _HEAP_H_

#ifdef CUSTOM_HEAP_ELEMENT
#include "heap_element.h"
#else
#define hel int
#define key(x) x
#endif

/* Sorting order; > is decreasing (default), < is increasing */
#ifndef HEAP_ORDER
#define HEAP_ORDER >
#endif

#define left(x) (2*x)+1
#define right(x) (2*x)+2
#define parent(x) ((x-1)/2)

typedef struct heap_t *heap;
struct heap_t
{
  hel *array;
  int size;
};

heap build_heap(hel *a, int s);
void heap_sort(hel *a, int s);

int heap_size(heap h);
void heap_insert(heap h, hel e);
hel heap_extract(heap h);

void _print_array(int *a, int s);

#endif /* _HEAP_H_ */
