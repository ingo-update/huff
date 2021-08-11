/* pak.c
 * Main function for the compression part of the huffman compression
 * programs.
 */

#include <stdlib.h>
#include <string.h>

#include "hist.h"
#include "encode.h"

void _print_usage(char *name)
{
  fprintf(stderr, "Usage:\n%s [-b, -h] <filename>\n", name);
}

int main(int argc, char **argv)
{
  FILE *infile, *outfile;
  char *filename;
  int print_bit_strings;
  int hist[256];
  int i;
  char outname[100];

  /* Check arguments */
  if (argc >= 2 && argv[1][0] == '-')
    if (argv[1][1] == 'h')
      {
	_print_usage(argv[0]);
	exit(EXIT_SUCCESS);
      }
    else if (argv[1][1] == 'b') /* Print all bitstrings to stdout */
      {
	if (argc != 3) /* Filename required */
	  {
	    _print_usage(argv[0]);
	    exit(EXIT_FAILURE);
	  }
	else
	  {
	    print_bit_strings = 1;
	    filename = argv[2];
	  }
      }
    else /* Illegal argument*/
      {
	_print_usage(argv[0]);
	exit(EXIT_FAILURE);
      }
  else if (argc == 2)
    {
      print_bit_strings = 0;
      filename = argv[1];
    }
  else
    {
      _print_usage(argv[0]);
      exit(EXIT_FAILURE);
    }

  /* Zero the histogram array. */
  for (i = 0 ; i < 256 ; ++i) hist[i] = 0;

  /* Open the input file to create character histogram. */
  infile = fopen(filename ,"r");
  if (NULL == infile)
    {
      fprintf(stderr, "Could not open input file '%s'.\n", filename);
      exit(EXIT_FAILURE);
    }

  /* Count input characters. */
  while (!feof(infile)) if (!feof(infile)) ++hist[fgetc(infile)];

  /* Close the infile. */
  fclose(infile);

  /* Create output file name. (TODO: Should be smarter.) */
  strncpy(outname, filename, 95);
  strncat(outname, SUFFIX, 95);

  /* Open the files for compression. */
  infile = fopen(filename, "r");
  if (NULL == infile)
    {
      fprintf(stderr, "Could not open input file '%s'.\n", filename);
      exit(EXIT_FAILURE);
    }

  outfile = fopen(outname, "w");
  if (NULL == outfile)
    {
      fprintf(stderr, "Could not open output file '%s'.\n", outname);
      exit(EXIT_FAILURE);
    }

  /* Output the histogram. */
  hist_store(outfile, hist);

  /* Compress infile to outfile. */
  encode(infile, outfile, hist, print_bit_strings);

  /* Close files. */
  fclose(infile);
  fclose(outfile);

  return EXIT_SUCCESS;
}
