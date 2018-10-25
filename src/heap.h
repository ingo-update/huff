#ifndef _HEAP_H_
#define _HEAP_H_

#include "hufftree.h"

/* Datatype */
/* hel is the heap element datatype, key(x) is the key function */

#define hel hufftree
#define key(x) (x->weight)

/* Sorting order; > is decreasing (default), < is increasing */
#ifndef HEAP_ORDER
#define HEAP_ORDER >
#endif

#define left(x) (2*x)
#define right(x) (2*x+1)
#define parent(x) (x/2)

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


#endif /* _HEAP_H_ */
