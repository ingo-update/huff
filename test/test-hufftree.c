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
  else if ('a' != hufftree_char(d))
    {
      fprintf(stderr, "FAIL, left branch is '%c', should be 'a'\n", hufftree_char(d));
      ++fail;
    }

  if (NULL == e)
    {
      fprintf(stderr, "FAIL, no right branch of linked tree\n");
      ++fail;
    }
  else if ('b' != hufftree_char(e))
    {
      fprintf(stderr, "FAIL, right branch is '%c', should be 'b'\n", hufftree_char(e));
      ++fail;
    }

  if (c->weight != 42 + 17)
    {
      fprintf(stderr, "FAIL, combined weight is %d, should be %d\n", c->weight, 42 + 17);
      ++fail;
    }

  return fail;
}

int main()
{
  int fail = 0;

  fail += test_datatype();

  fprintf(stdout, "test_hufftree: ");
  if (0 == fail)
    {
      fprintf(stdout, "SUCCESS\n");
      exit(EXIT_SUCCESS);
    }
  else
    {
      fprintf(stdout, "FAILURE; %d tests failed.\n", fail);
      exit(EXIT_FAILURE);
    }
}
