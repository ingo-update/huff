/* encode.c
 * Encoding routine for the huffman compression programs.
 */

#include <stdio.h>
#include <stdlib.h>

#include "hufftree.h"
#include "bitstring.h"

void encode(FILE *infile, FILE *outfile, int *hist)
{
  unsigned char outc, inc;
  int i, outp, inp, bit;
  hufftree t;
  bitstring b;
  bitstring *bs;

  /* Create the hufftree. */
  t = hufftree_build(hist);

  /* Allocate the bitstring pointer array. */
  bs = (bitstring *) malloc(sizeof(bitstring *) * 256);
  if (NULL == bs)
    {
      fprintf(stderr,"encode() - Couldn't allocate the bitstring array.\n");
      exit(EXIT_FAILURE);
    }

  /* Build bitstring array from the tree. */
  hufftree_scan(t, bitstring_empty(), bs);

  /* Encode all characters in the file. */
  outp = 7; outc = 0;
  while (!feof(infile))
    {
      /* Read input character. */
      inc = fgetc(infile);
      if (!feof(infile))
	{
	  /* Select bitstring. */
	  b = bs[inc];
	  inp = b->length-1;

	  /* Output all bits in the bitstring. */
	  while (0 <= inp)
	    {
	      bit = bitstring_bit(b, inp--);
	      outc = (outc | (bit << outp--));

	      /* Send full bytes to output file. */
	      if (0 > outp)
		{
		  fputc(outc, outfile);
		  outp = 7 ; outc = 0;
		}
	    }
	}
    }

  /* If a byte was not finished, output it anyway. */
  if (7 != outp) fputc(outc, outfile);

  /* Free the bitstring array and its content. */
  for (i = 0 ; i < 256 ; ++i) if (bs[i]) bitstring_remove(bs[i]);
  free(bs);

  return;
}
