#include <stdlib.h>
#include <stdio.h>

#include "hufftree.h"

#define WEIGHT_L 17
#define CHAR_L 'x'
#define WEIGHT_H 4711
#define CHAR_H 'y'

int test_datatype()
{
  int fail;
  hufftree a, b, c, d, e;

  fail = 0;

  a = hufftree_leaf(CHAR_L, WEIGHT_L);
  b = hufftree_leaf(CHAR_H, WEIGHT_H);
  c = hufftree_link(a, b);

  if (NULL == a)
    {
      fprintf(stderr, "FAIL, couldn't create first hufftree leaf\n");
      ++fail;
    }
  else if (!hufftree_is_leaf(a))
    {
      fprintf(stderr, "FAIL, first tree should be a leaf\n");
      ++fail;
    }

  if (NULL == b)
    {
      fprintf(stderr, "FAIL, couldn't create second hufftree leaf\n");
      ++fail;
    }
  else if (!hufftree_is_leaf(b))
    {
      fprintf(stderr, "FAIL, second tree should be a leaf\n");
      ++fail;
    }

  if (NULL == c)
    {
      fprintf(stderr, "FAIL, couldn't link hufftrees\n");
      ++fail;
    }
  else if (hufftree_is_leaf(c))
    {
      fprintf(stderr, "FAIL, third tree should not be a leaf\n");
      ++fail;
    }

  d = hufftree_left(c);
  e = hufftree_right(c);

  if (NULL == d)
    {
      fprintf(stderr, "FAIL, no left branch of linked tree\n");
      ++fail;
    }
  else if (CHAR_L != hufftree_char(d))
    {
      fprintf(stderr, "FAIL, left branch is '%c', should be '%c'\n", hufftree_char(d), CHAR_L);
      ++fail;
    }

  if (NULL == e)
    {
      fprintf(stderr, "FAIL, no right branch of linked tree\n");
      ++fail;
    }
  else if (CHAR_H != hufftree_char(e))
    {
      fprintf(stderr, "FAIL, right branch is '%c', should be '%c'\n", hufftree_char(e), CHAR_H);
      ++fail;
    }

  if (c->weight != WEIGHT_L + WEIGHT_H)
    {
      fprintf(stderr, "FAIL, combined weight is %d, should be %d\n", c->weight, WEIGHT_L + WEIGHT_H);
      ++fail;
    }

  return fail;
}

int main()
{
  int fail = 0;

  fprintf(stdout, "test-hufftree: ");
  fail += test_datatype();

  if (0 == fail)
    {
      fprintf(stdout, "SUCCESS\n");
      return EXIT_SUCCESS;
    }
  else
    {
      fprintf(stdout, "FAILURE; %d tests failed.\n", fail);
      return EXIT_FAILURE;
    }
}
