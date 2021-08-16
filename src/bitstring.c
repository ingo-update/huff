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
 * Create a new bitstring with a new bit added at the right.
 */

bitstring bitstring_add(bitstring bs, int bit)
{
  bitstring new;

  if (NULL == bs)
    {
      fprintf(stderr,"bitstring_add() - bitstring uninitialized (NULL).\n");
      return NULL;
    }

  if (sizeof(long long) * 8 <= bs->length)
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
      return -1;
    }
  else if (b > bs->length)
    {
      fprintf(stderr,"bitstring_bit() - bit outside string requested.\n");
      return -2;
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

/* bitstring_2s()
 * Return a string of 1s and 0s representing the bitstring.
 */

void bitstring_2s(bitstring bs, char *str)
{
  int i;
  for (i = 0 ; i < bs->length ; ++i)
    {
      str[i] = ((bs->bits >> (i)) & 0x1) ? '1' : '0';
    }
  str[bs->length] = '\0';

  return;
}

/* bitstring_print()
 * Print the bits from a bitstring on a output stream.
 */

void bitstring_print(FILE *s, bitstring bs)
{
  char *str;

  if (NULL == bs) return;

  str = (char *) malloc(sizeof(char) * bs->length + 1);
  if (NULL == str)
    {
      fprintf(stderr,"bitstring_print() - could not allocate string.\n");
    }

  bitstring_2s(bs, str);
  fprintf(s, "[%s]", str);
  free(str);

  return;
}
