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
  int l, r, s, x;

  l = left(i);
  r = right(i);
  s = a->size;

  /* Try to find exchange candidate */
  x = ((l < s) && heap_order(a->array[l], a->array[i])) ? l : i;
  x = ((r < s) && heap_order(a->array[r], a->array[x])) ? r : x;

  /* Exchange and heapify subtree if candidate was found */
  if (x != i)
    {
      _exchange(a->array, i, x);
      _heapify(a, x);
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

  /* The last half ot the array are guaranteed to be leaf nodes */
  for (i = (s/2)-1 ; i >= 0 ; --i)
    {
      _heapify(new, i);
    }

  return new;
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

  /* Start at the end of the array */
  i = a->size;

  /* Pull elements down until we find the correct place to insert */
  while ((i > 0) && heap_order(e, a->array[parent(i)]))
    {
      a->array[i] = a->array[parent(i)];
      i = parent(i);
    }

  /* Insert and increase heap size */
  a->array[i] = e;
  ++a->size;

  return;
}

/* heap_extract()
 * extract the top element from a heap, maintain heap property in the
 * remaining data.
 */

heap_element heap_extract(heap a)
{
  heap_element x;

  if (a->size < 1)
    {
      fprintf(stderr,"heap_extract() - Heap underflow.\n");
      exit(EXIT_FAILURE);
    }

  /* Remove first element and put the last one first, decreasing the size */
  x = a->array[0];
  a->array[0] = a->array[--a->size];

  /* Restore heap property */
  _heapify(a, 0);

  return x;
}

/* heap_sort()
 * Sort an array using heap sort.
 */

#ifndef OMIT_HEAP_SORT
void heap_sort(heap_element *a, int s)
{
  heap h;
  int i;

  /* Build a heap of the array */
  h = build_heap(a, s);

  for (i = s - 1 ; i >= 0 ; --i)
    {
      /* Exchange the top element of the heap with the last one */
      _exchange(h->array, 0, i);

      /* Decrease size and heapify */
      --h->size;
      _heapify(h, 0);
    }

  /* Throw away the heap wrapper */
  free(h);
}
#endif // OMIT_HEAP_SORT
