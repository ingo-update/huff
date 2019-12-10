#include <stdlib.h>
#include <stdio.h>

#include "hufftree.h"

int test_datatype()
{
  int fail;
  hufftree a, b, c, d, e;

  fail = 0;

  a = hufftree_leaf('a', 17);
  b = hufftree_leaf('b', 42);
  c = hufftree_link(a, b);

  if (!hufftree_is_leaf(a))
    {
      fprintf(stderr, "FAILURE, tree a should be a leaf!\n");
      ++fail;
    }
  if (!hufftree_is_leaf(b))
    {
      fprintf(stderr, "FAILURE, tree a should be a leaf!\n");
      ++fail;
    }
  if (hufftree_is_leaf(c))
    {
      fprintf(stderr, "FAILURE, tree a should not be a leaf!\n");
      ++fail;
    }

  d = hufftree_left(c);
  e = hufftree_right(c);

  if (NULL == d)
    {
      fprintf(stderr, "FAILURE, no left branch of c\n");
      ++fail;
    }
  else if ('a' != hufftree_char(d))
    {
      fprintf(stderr, "FAILURE, left branch is '%c', should be 'a'\n", hufftree_char(d));
      ++fail;
    }

  if (NULL == e)
    {
      fprintf(stderr, "FAILURE, no right branch of c\n");
      ++fail;
    }
  else if ('b' != hufftree_char(e))
    {
      fprintf(stderr, "FAILURE, right branch is '%c', should be 'b'\n", hufftree_char(e));
      ++fail;
    }

  if (c->weight != 42 + 17)
    {
      fprintf(stderr, "FAILURE, combined weight is %d, should be %d\n", c->weight, 42 + 17);
      ++fail;
    }

  return fail;
}

int main()
{
  int fail = 0;

  if (!fail)
    {
      fail += test_datatype();
    }

  if (fail)
    {
      fprintf(stderr, "FAILURE, %d tests failed\n", fail);
      return EXIT_FAILURE;
    }
  else
    {
      fprintf(stderr, "SUCCESS\n");
      return EXIT_SUCCESS;
    }
}
