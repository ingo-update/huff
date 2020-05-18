/* hist.c
 * Handle loading and storing of the histogram in the compressed file for
 * the huffman compression programs.
 */

#include <stdio.h>
#include <stdlib.h>

/* _write_int() - Write an int so that it can be read by _read_int()
 */

static void _write_int(FILE *s, int i)
{
  fprintf(s, "%d\n", i);
}

/* _read_int() - Read an int written by _write_int()
 */

static int _read_int(FILE *s)
{
  int i, c;

  i = c = 0;
  while ('\n' != c)
    {
      c = fgetc(s);
      if (('0' <= c) && ('9' >= c))
	{
	  i = i * 10 + (c - '0');
	}
    }

  return i;
}

void hist_store(FILE *s, int *hist)
{
  unsigned char c;

  for (c = 0 ; c < 255 ; ++c)
    {
      if (0 < hist[c])
	{
	  /* Output character */
	  fputc((unsigned char) c, s);

	  /* Output frequency */
	  _write_int(s, hist[c]);
	}
    }

  /* Print stop mark (zero frequency) */
  fputs("00\n", s);

  return;
}

void hist_load(FILE *s, int *hist)
{
  unsigned char c, pc;
  int i;
  int f = 1;

  /* Clear histogram */
  for (i = 0 ; i < 256 ; ++i) hist[i] = 0;

  /* Read frequency data into histogram */
  c = 0;
  while (0 != f)
    {
      /* Get character and frequency */
      pc = c;
      c = fgetc(s);

      f = _read_int(s);

      /* Check for stop mark */
      if (0 != f)
	{
	  if ((c <= pc) && (c != 0))
	    {
	      fprintf(stderr, "hist_load(): Error in histogram, %d (%c) not allowed after %d (%c).\n", c, c, pc, pc);
	      exit(EXIT_FAILURE);
	    }

     	  hist[c] = f;
	}
    }

  return;
}
