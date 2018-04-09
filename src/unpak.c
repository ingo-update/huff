/* unpak.c
 * Main function for the decompression part of the huffman compression 
 * programs.
 */

#include <stdio.h>
#include <string.h>

#include "hist.h"
#include "decode.h"

int main(int argc, char **argv)
{
  FILE *infile;
  FILE *outfile;
  char outname[100];
  int hist[256];
  
  /* Create output file name. (Could be smarter.) */
  strncpy(outname, argv[1], 95);
  outname[strlen(outname)-4] = '\0';

  /* Open the files. */
  infile = fopen(argv[1], "r");
  outfile = fopen(outname, "w");
  
  /* Load the histogram. */
  hist_load(infile, hist);
  
  /* Decompress infile to outfile. */
  decode(infile, outfile, hist);
  
  /* Done, close files. */
  fclose(infile);
  fclose(outfile);
 
  return(0);
}
