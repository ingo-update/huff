#ifndef _HUFFTREE_H_
#define _HUFFTREE_H_

#include "bitstring.h"

/* Maxumum function. */
#define max(x,y) (x > y ? x : y)

typedef struct hufftree_t *hufftree;
struct hufftree_t
{
  hufftree left;
  hufftree right;

  unsigned char c;
  int weight;
};

/* Constructors. */
hufftree hufftree_leaf(unsigned char c, int weight);
hufftree hufftree_link(hufftree l, hufftree r);

/* Selectors. */
hufftree hufftree_left(hufftree t);
hufftree hufftree_right(hufftree t);
int hufftree_is_leaf(hufftree t);
unsigned char hufftree_char(hufftree t);

/* Miscellaneous. */
hufftree hufftree_build(int *hist);
void hufftree_scan(hufftree t, bitstring a, bitstring *bs);

#endif /* _HUFFTREE_H_ */
