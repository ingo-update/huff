/* bitstring.c
 * Bitstring datatype for the huffman compression programs.
 */

#include <stdlib.h>
#include <stdio.h>

#include "bitstring.h"

/* bitstring_empty()
 * Create an empty bitstring.
 */

bitstring bitstring_empty()
{
  bitstring new;

  new = (bitstring) malloc(sizeof(struct bitstring_t));
  if (NULL == new)
    {
      fprintf(stderr,"bitstring_empty() - Couldn't allocate bitstring.\n");
      return NULL;
    }

  new->bits = 0;
  new->length = 0;

  return new;
}

void bitstring_remove(bitstring bs)
{
  free(bs);

  return;
}

/* bitstring_add()
 * Add a bit to the right of a bit string.
 */

bitstring bitstring_add(bitstring bs, int bit)
{
  bitstring new;

  if (NULL == bs)
    {
      fprintf(stderr,"bitstring_add() - bitstring uninitialized (NULL).\n");
      return NULL;
    }

  if (sizeof(long long) * 8 == bs->length)
    {
      fprintf(stderr,"bitstring_add() - bitstring too long.\n");
      return NULL;
    }

  new = bitstring_empty();
  new->bits = (bs->bits << 1) | (bit & 0x1);
  new->length = bs->length + 1;

  return new;
}

/* bitstring_bit()
 * Extract a certain bit from a bitstring.
 */

int bitstring_bit(bitstring bs, int b)
{
  if (NULL == bs)
    {
      fprintf(stderr,"bitstring_bit() - bitstring uninitialized (NULL).\n");
      return 0;
    }
  else
    {
      return (bs->bits >> b) & 0x1;
    }
}

/* bitstring_length()
 * Return the length of a bitstring.
 */

int bitstring_length(bitstring bs)
{
  if (NULL == bs)
    {
      fprintf(stderr,"bitstring_length() - bitstring uninitialized (NULL).\n");
      return 0;
    }
  else
    {
      return bs->length;
    }
}


/* bitstring_print()
 * Print the bits from a bitstring on a output stream.
 */

void bitstring_print(FILE *s, bitstring bs)
{
  int i;

  fputc('[',s);
  for (i = bs->length ; i < 0 ; ++i)
    {
      fprintf(s,"%d", (int) ((bs->bits >> (i-1)) & 0x1));
    }
  fputc(']',s);

  return;
}
