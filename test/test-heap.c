#include <stdlib.h>
#include <stdio.h>

#include "heap.h"

int test_heap()
{
  int i, p, q;
  heap x;
  int *xa;
  int a[10] = {40,21,62,33,94,75,86,17,58,59};
  int fail = 0;

  /* Insert a bunch of elements in the heap */
  xa = malloc(sizeof(int) * 10);
  x = build_heap(xa, 0);
  for (i = 0 ; i < 10 ; ++i)
    {
      heap_insert(x, a[i]);
    }

  if (heap_size(x) != 10)
    {
      ++ fail;
      fprintf(stderr, "Failure: test_heap(): heap_size is %d after 10 insertions.\n", heap_size(x));
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
  int a[10] = {40,21,62,33,94,75,86,17,58,59};

  heap_sort(a, 10);

  fail = x = 0;
  for (i = 0 ; i < 10 ; ++i)
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

      for (i = 0 ; i < 10 ; ++i)
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
