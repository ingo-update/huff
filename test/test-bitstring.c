#include "stdlib.h"

#include "bitstring.h"

int test_bitstrings()
{
  int i, fail;
  bitstring b = NULL;

  fail = 0;

  if (0 != bitstring_length(b))
    {
      ++fail;
      fprintf(stderr, "FAIL: Uninitialized bitstring has unexpected length %d.\n", bitstring_length(b));
    }

  b = bitstring_add(b, 0);
  if (NULL != b)
    {
      ++fail;
      fprintf(stderr, "FAIL: Could add to uninitialized bitstring.\n");
    }

  b = bitstring_empty();
  if (NULL == b)
    {
      ++fail;
      fprintf(stderr, "FAIL: Could not create empty bitstring.\n");
    }
  else if (0 != bitstring_length(b))
    {
      ++fail;
      fprintf(stderr, "FAIL: Empty bitstring should not have length %d.\n", bitstring_length(b));
    }

  for (i = 0 ; i < 10 ; ++i)
    {
      b = bitstring_add(b, i);
    }

  if (10 != bitstring_length(b))
    {
      ++fail;
      fprintf(stderr, "FAIL: Bitstring with 10 bits should not have length %d.\n", bitstring_length(b));
    }
  else if (1 != bitstring_bit(b, 2))
    {
      ++fail;
      fprintf(stderr, "FAIL: Bit 2 should not be a %d, it should be 1.\n", bitstring_bit(b, 2));
    }
  else if (0 != bitstring_bit(b, 5))
    {
      ++fail;
      fprintf(stderr, "FAIL: Bit 5 should not be a %d, it should be 0.\n", bitstring_bit(b, 5));
    }

  b = bitstring_empty();
  for (i = 0 ; i < 65 ; ++i)
    {
      b = bitstring_add(b, i);
    }
  if (NULL != b)
    {
      ++fail;
      fprintf(stderr, "FAIL: Could build too long bitstring.\n");
    }
  return fail;
}


int main()
{
  int fail;

  fail = 0;

  fail += test_bitstrings();

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
