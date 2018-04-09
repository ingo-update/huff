/* pak.c
 * Main function for the compression part of the huffman compression 
 * programs.
 */

#include <stdlib.h>
#include <string.h>

#include "hist.h"
#include "encode.h"

int main(int argc, char **argv)
{
  FILE *infile, *outfile;
  int hist[256];
  int i;
  unsigned char inc;
  char outname[100];

  /* Open the input file to create character statistics. */
  infile = fopen(argv[1] ,"r");

  /* Zero the histogram array. */
  for (i = 0 ; i < 256 ; ++i)
    {
      hist[i] = 0;
    }

  /* Count input characters. */
  while (!feof(infile))
    {
      inc = fgetc(infile);
      if (!feof(infile))
	{
	  ++ hist[inc];
	}
    }

  /* Close the infile. */
  fclose(infile);

  /* Create output file name. (Could be smarter.) */
  strncpy(outname, argv[1], 95);
  strncat(outname, SUFFIX, 95);

  /* Open the files for compression. */
  infile = fopen(argv[1], "r");
  outfile = fopen(outname, "w");

  /* Output the histogram. */
  hist_store(outfile, hist);

  /* Compress infile to outfile. */
  encode(infile, outfile, hist);

  /* Close files. */
  fclose(infile);
  fclose(outfile);

  return 0;
}
