/* heap.c
 * A general heap datatype.
 */

#include <stdlib.h>
#include <stdio.h>

#include "heap.h"

/* Exchange two elements in the heap array. */

static void _exchange(heap_element *a, int x, int y)
{
  heap_element t;

  t = a[x];
  a[x] = a[y];
  a[y] = t;

  return;
}

/* Restore the heap property in a heap rooted in i where both subtrees are
 * heaps. */

static void _heapify(heap a, int i)
{
  int l,r,x;

  l = left(i);
  r = right(i);

  if ((l < a->size) && heap_order(a->array[l], a->array[i]))
    {
      x = l;
    }
  else
    {
      x = i;
    }

  if ((r < a->size) && heap_order(a->array[r], a->array[x]))
    {
      x = r;
    }

  if (x != i)
    {
      _exchange(a->array,i,x);
      _heapify(a,x);
    }

  return;
}

/* build_heap()
 * make an array into a heap.
 */

heap build_heap(heap_element *a, int s)
{
  heap new;
  int i;

  new = (heap) malloc(sizeof(struct heap_t));
  if (NULL == new)
    {
      fprintf(stderr,"build_heap() - Couldn't allocate memory.\n");
      exit(EXIT_FAILURE);
    }

  new->array = a;
  new->size = s;
  for (i = (s/2)-1 ; i >= 0 ; --i)
    {
      _heapify(new, i);
    }

  return new;
}

/* heap_sort() Sort an array using heapsort. Not used by the huffman
 * compression programs.
 */

void heap_sort(heap_element *a, int s)
{
  heap h;
  int i;

  h = build_heap(a, s);

  for (i = s-1 ; i >= 0 ; --i)
    {
      _exchange(h->array, 0, i);
      --h->size;
      _heapify(h,0);
    }

  free(h);
}

/* heap_size()
 * return the current size of a heap.
 */

int heap_size(heap a)
{
  return a->size;
}

/* heap_insert()
 * insert an element into a heap.
 */

void heap_insert(heap a, heap_element e)
{
  int i;

  i = a->size;

  while ((i > 0) && heap_order(e, a->array[parent(i)]))
    {
      a->array[i] = a->array[parent(i)];
      i = parent(i);
    }

  ++a->size;
  a->array[i] = e;

  return;
}

/* heap_extract()
 * extract the top element from a heap, maintain heap property in the
 * remaining data.
 */

heap_element heap_extract(heap a)
{
  heap_element max;

  if (a->size < 1)
    {
      fprintf(stderr,"heap_extract() - Heap underflow.\n");
      exit(-1);
    }

  max = a->array[0];
  a->array[0] = a->array[a->size-1];
  --a->size;
  _heapify(a,0);

  return max;
}
