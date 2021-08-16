#include <stdlib.h>
#include <stdio.h>

#include "hist.h"

#define TEST_FILE_NAME "build/test/testfile"
#define TEST_HIST_FILE "build/test/histfile"

int test_hist()
{
  int fail;
  FILE *infile, *histfile;
  int hist0[256];
  int hist1[256];
  int i;
  unsigned char inc;

  fail = 0;

  infile = fopen(TEST_FILE_NAME ,"r");
  if (NULL == infile)
    {
      fprintf(stdout, "Could not open input file '%s'.\n", TEST_FILE_NAME);
      return 1;
    }

  for (i = 0 ; i < 256 ; ++i) hist0[i] = 0;

  while (!feof(infile))
    {
      inc = fgetc(infile);
      if (!feof(infile)) ++hist0[inc];
    }

  fclose(infile);

  /* Test that hist_store and hist_load keep histogram integrity. */

  histfile = fopen(TEST_HIST_FILE, "w");
  hist_store(histfile, hist0);
  fclose(histfile);

  histfile = fopen(TEST_HIST_FILE, "r");
  hist_load(histfile, hist1);
  fclose(histfile);

  for (i = 0 ; i < 256 ; ++i)
    {
      if (hist0[i] != hist1[i])
	{
	  fprintf(stderr, "FAIL: Histograms differ at char '%c'(0x%2x), (%d != %d)\n", i, i, hist0[i], hist1[i]);
	  ++fail;
	}
    }

  return fail;
}

int main()
{
  int fail;

  fprintf(stdout, "test-hist: ");
  fail = 0;

  fail += test_hist();

  if (0 == fail)
    {
      fprintf(stdout, "SUCCESS\n");
      return EXIT_SUCCESS;
    }
  else
    {
      fprintf(stdout, "FAILURE: %d failures detected.\n", fail);
      return EXIT_FAILURE;
    }
}
