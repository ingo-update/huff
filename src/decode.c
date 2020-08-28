/* decode.c
 * Decoding routine for the huffman compression programs.
 */

#include <stdio.h>

#include "hufftree.h"

void decode(FILE *infile, FILE *outfile, int *hist)
{
  unsigned char inc;
  int i, j, len, bit;
  hufftree tree, tp;

  /* Count characters in histogram (= length of original data). */
  len = 0;
  for (i = 0 ; i < 255 ; ++i) len += hist[i];

  /* Build the tree. */
  tree = hufftree_build(hist);

  /* Output as many characters as the original file. */
  i = 0 ; tp = tree;
  while (i < len)
    {
      /* Read a new byte. */
      inc = fgetc(infile);

      /* Go through the tree bit by bit. */
      for (j = 7 ; j >= 0 ; --j)
	{
	  bit = (inc >> j) & 0x1;

	  /* Follow left or right depending on value of bit. */
	  tp = (bit ? hufftree_right(tp) : hufftree_left(tp));

	  /* Found a leaf yet? */
	  if (hufftree_is_leaf(tp))
	    {
	      /* Output character and go back to the top of the tree. */
	      fputc(hufftree_char(tp), outfile);
	      tp = tree;
	      ++i;

	      /* Done yet? */
	      if (i == len) break;
	    }
	}
    }

  return;
}
