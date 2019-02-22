#include <stdlib.h>

#include "heap.h"

int test_heap()
{
  return 0;
}

int test_heapsort()
{
  return 0;
}

int main()
{
  int fail;

  fail = 0;

  fail += test_heap();

  fail += test_heapsort();

    if (fail)
    {
      fprintf(stderr, "FAILURE: %d failures detected.\n", fail);
      return EXIT_FAILURE;
    }
  else
  {
    return EXIT_SUCCESS;
  }
}
