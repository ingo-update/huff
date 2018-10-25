#ifndef _BITSTRING_H_
#define _BITSTRING_H_

#include <stdio.h>

typedef struct bitstring_t *bitstring;
struct bitstring_t
{
  long long bits;
  int length;
};

/* Constructors/Destructors. */
bitstring bitstring_empty();
void bitstring_remove(bitstring bs);
bitstring bitstring_add(bitstring bs, int bit);

/* Selectors. */
int bitstring_bit(bitstring bs, int b);
int bitstring_length(bitstring bs);

/* Miscellaneous. */
void bitstring_print(FILE *s, bitstring bs);

#endif /* _BITSTRING_H_ */
