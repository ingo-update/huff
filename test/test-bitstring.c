#include <stdlib.h>
#include <string.h>

#include "bitstring.h"

/* Must be odd and greater than 5 */
#define TESTSTRING_LENGTH 25

int test_bitstrings()
{
  int i, fail;
  bitstring b;
  char *c1, *c2;

  fail = 0;

  /* Prepare some test strings */
  c1 = (char *) malloc(sizeof(char) * TESTSTRING_LENGTH);
  c2 = (char *) malloc(sizeof(char) * TESTSTRING_LENGTH);
  if (NULL == c1 || NULL == c2)
    {
      ++fail;
      fprintf(stderr, "ERROR: Could not allocate test strings.\n");
      return fail;
    }

  /* Alternating zeroes and ones */
  for (i = 0 ; i < TESTSTRING_LENGTH ; ++i) c2[i] = i & 0x1 ? '1' : '0';

  /* Test behaviour when bitstring is uninitialized */
  b = NULL;
  if (0 != bitstring_length(b))
    {
      ++fail;
      fprintf(stderr, "FAIL: Uninitialized bitstring has unexpected length %d.\n", bitstring_length(b));
    }

  i = bitstring_bit(b, 17);
  if (-1 != i)
    {
      ++fail;
      fprintf(stderr, "FAIL: Could read bit from uninitialized bitstring.\n");
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

  /* Build bitstring with alternating bits. Even bits 0 and odd bits 1*/
  for (i = 0 ; i < TESTSTRING_LENGTH ; ++i)
    {
      b = bitstring_add(b, i & 0x1);
      if (NULL == b)
	{
	  ++fail;
	  fprintf(stderr, "ERROR: Could not add bit number %d to a bitstring (bitstring too long).\n", i);
	  return fail;
	}
    }

  /* Test that bitstring was created corretly */
  if (TESTSTRING_LENGTH != bitstring_length(b))
    {
      ++fail;
      fprintf(stderr, "FAIL: Bitstring with %d bits should not have length %d.\n", TESTSTRING_LENGTH, bitstring_length(b));
    }
  if (0 != bitstring_bit(b, 2))
    {
      ++fail;
      fprintf(stderr, "FAIL: Bit 2 should not be a %d, it should be a 0.\n", bitstring_bit(b, 2));
    }
  if (1 != bitstring_bit(b, 5))
    {
      ++fail;
      fprintf(stderr, "FAIL: Bit 5 should not be a %d, it should be a 1.\n", bitstring_bit(b, 5));
    }

  i = bitstring_bit(b, TESTSTRING_LENGTH + 1);
  if (-2 != i)
    {
      ++fail;
      fprintf(stderr, "FAIL: Could read bit outside of bitstring.\n");
    }

  /* Test string conversion */
  bitstring_2s(b, c1);
  if (strncmp(c1, c2, TESTSTRING_LENGTH))
    {
      ++fail;
      fprintf(stderr, "FAIL: String conversion failed. Got '%s', expected '%s'.\n", c1, c2);
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

  fprintf(stdout, "test-bitstring: ");
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
