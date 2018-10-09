/* unpak.c
 * Main function for the decompression part of the huffman compression
 * programs.
 */

#include <stdlib.h>
#include <string.h>

#include "hist.h"
#include "decode.h"

int main(int argc, char **argv)
{
  FILE *infile;
  FILE *outfile;
  char outname[100];
  int hist[256];

  /* Check that we got exactly one argument. */
  if (2 != argc)
    {
      fprintf(stderr, "Usage:\n%s <filename>.pak\n", argv[0]);
      exit(EXIT_FAILURE);
    }

  /* Create output file name. (TODO: Could be smarter.) */
  strncpy(outname, argv[1], 95);
  outname[strlen(outname)-4] = '\0';

  /* Open the files. */
  infile = fopen(argv[1], "r");
  if (NULL == infile)
    {
      fprintf(stderr, "Could not open input file '%s'.\n", argv[1]);
      exit(EXIT_FAILURE);
    }

  outfile = fopen(outname, "w");
  if (NULL == outfile)
    {
      fprintf(stderr, "Could not open output file '%s'.\n", outname);
      exit(EXIT_FAILURE);
    }

  /* Load the histogram. */
  hist_load(infile, hist);

  /* Decompress infile to outfile. */
  decode(infile, outfile, hist);

  /* Done, close files. */
  fclose(infile);
  fclose(outfile);

  return EXIT_SUCCESS;
}
