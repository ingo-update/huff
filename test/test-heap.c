#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "heap.h"

#define HEAPSIZE 100000

int test_heap()
{
  int i, p, q;
  heap x;
  int *xa;
  int fail = 0;

  /* Randomize */
  srand(time(0));

  /* Create an empty heap and insert a bunch of random ints into it */
  xa = malloc(sizeof(int) * HEAPSIZE);
  x = build_heap(xa, 0);
  for (i = 0 ; i < HEAPSIZE ; ++i) heap_insert(x, rand());

  /* Check that size increased correctly */
  if (heap_size(x) != HEAPSIZE)
    {
      ++ fail;
      fprintf(stderr, "Failure: test_heap(): heap_size is %d after %d insertions.\n", heap_size(x), HEAPSIZE);
    }

  /* Extract elements in correct order */
  p = heap_extract(x);
  while (heap_size(x) > 0)
    {
      q = heap_extract(x);
      if (p < q)
	{
	  ++ fail;
	  fprintf(stderr, "Failure: test_heap(): Out of order elements; %d should not be smaller than %d.\n", p, q);
	}
      p = q;
    }

  return fail;
}

int test_heapsort()
{
  int fail, i, x;
  int *a;

  /* Randomize */
  srand(time(0));

  /* Make a random array */
  a = malloc(sizeof(int) * HEAPSIZE);
  for (i = 0 ; i < HEAPSIZE ; ++i) a[i] = rand();

  /* Sort the array */
  heap_sort(a, HEAPSIZE);

  /* Check that it is sorted */
  fail = x = 0;
  for (i = 0 ; i < HEAPSIZE ; ++i)
    {
      if (a[i] < x)
	{
	  fail = 1;
	}
      else
	{
	  x = a[i];
	}
    }

  if (fail)
    {
      fprintf(stderr, "Failure: test_heapsort() Array is not correctly sorted:");

      for (i = 0 ; i < HEAPSIZE ; ++i)
	{
	  fprintf(stderr, " %d", a[i]);
	}
      fprintf(stderr, "\n");
    }

  return fail;
}

int main()
{
  int fail;

  fail = 0;

  fail += test_heap();
  fail += test_heapsort();

  fprintf(stdout, "test_heap: ");
  if (0 == fail)
    {
      fprintf(stdout, "SUCCESS\n");
      exit(EXIT_SUCCESS);
    }
  else
    {
      fprintf(stderr, "FAILURE: %d failures detected.\n", fail);
      return EXIT_FAILURE;
    }
}
