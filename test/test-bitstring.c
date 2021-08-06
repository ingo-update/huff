#include <stdlib.h>
#include <string.h>

#include "bitstring.h"

int test_bitstrings()
{
  int i, fail;
  bitstring b;
  char *c1;
  char *c2 = "1010101010";

  fail = 0;

  /* Test behaviour when bitstring is uninitialized */
  b = NULL;
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

  /* Test empty bitstring */
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

  /* Build bitstring with 10 alternating bits [1010101010]*/
  for (i = 0 ; i < 10 ; ++i)
    {
      b = bitstring_add(b, i);
    }

  /* Test that bitstring was created corretly */
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

  i = bitstring_bit(b, 11);
  if (0 == i || 1 == i)
    {
      ++fail;
      fprintf(stderr, "FAIL: Could read bit 11 of 10 bit bitstring.\n");
    }

  /* Prepare a test string */
  c1 = (char *) malloc(sizeof(char) * bitstring_length(b));
  if (NULL == c1)
    {
      ++fail;
      fprintf(stderr, "ERROR: Could not allocate test string.\n");
    }

  /* Test string conversion */
  bitstring_2string(b, c1);
  if (strncmp(c1, c2, 10))
    {
      ++fail;
      fprintf(stderr, "FAIL: String conversion failed. Got %s, expected %s.\n", c1, c2);
    }

  b = bitstring_empty();
  for (i = 0 ; i < 65 ; ++i) b = bitstring_add(b, i);
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

  fprintf(stdout, "test_bitstring: ");
  fail = 0;

  fail += test_bitstrings();

  if (0 == fail)
    {
      fprintf(stdout, "SUCCESS\n");
      return EXIT_SUCCESS;
    }
  else
    {
      fprintf(stdout, "FAILURE: %d failures detected.\n", fail);
      return EXIT_FAILURE;
    }
}
