/* hufftree.c
 * Huffman compression tree for the huffman compression programs.
 *
 * A Huffman tree is either a leaf containing a character and the
 * weight of it (the number of times it appears in the input file) or
 * a node containing two subtrees and the combined weight of them.
 */

#include <stdlib.h>
#include <stdio.h>

#include "bitstring.h"
#include "heap.h"
#include "hufftree.h"

/* hufftree_leaf()
 * Create a huffman tree leaf.
 */

hufftree hufftree_leaf(unsigned char c, int weight)
{
  hufftree new;

  new = (hufftree) malloc(sizeof(struct hufftree_t));
  if (NULL == new)
    {
      fprintf(stderr,"hufftree_leaf() - Couldn't allocate leaf.\n");
      exit(EXIT_FAILURE);
    }

  new->left = new->right = NULL;
  new->weight = weight;
  new->c = c;

  return new;
}

/* hufftree_link()
 * link two huffman trees together.
 */

hufftree hufftree_link(hufftree l, hufftree r)
{
  hufftree new;

  new = (hufftree) malloc(sizeof(struct hufftree_t));
  if (NULL == new)
    {
      fprintf(stderr,"hufftree_link() - Couldn't allocate node.\n");
      exit(EXIT_FAILURE);
    }

  new->left = l;
  new->right = r;
  new->weight = (l->weight) + (r->weight);

  return new;
}

/* hufftree_left()
 * return the left subtree of a huffman tree.
 */

hufftree hufftree_left(hufftree t)
{
  return t->left;
}

/* hufftree_right()
 * return the right subtree of a huffman tree.
 */

hufftree hufftree_right(hufftree t)
{
  return t->right;
}

/* hufftree_is_leaf()
 * return 1 if the tree is a leaf, else 0.
 */

int hufftree_is_leaf(hufftree t)
{
  return (NULL == t->left);
}

/* hufftree_char()
 * return the char of a huffman tree leaf.
 */

unsigned char hufftree_char(hufftree t)
{
  return t->c;
}

/* hufftree_build
 * build and return a huffman tree from a character histogram.
 */

hufftree hufftree_build(int *hist)
{
  int i, size;
  heap a;
  hufftree *trees;

  /* Allocate an array for the trees. */
  trees = (hufftree *) malloc(sizeof(hufftree *) * 256);
  if (NULL == trees)
    {
      fprintf(stderr,"hufftree_build() - Couldn't allocate the tree array.\n");
      exit(EXIT_FAILURE);
    }

  /* Make hufftree leaves and put them into an array. */
  size = 0;
  for (i = 0 ; i < 255 ; ++i)
    {
      /* No zero-weight leaves! */
      if (0 < hist[i])
	{
	  trees[size] = hufftree_leaf((unsigned char) i, hist[i]);
	  ++size;
	}
    }

  /* Make a heap out of the array. */
  a = build_heap(trees, size);

  /* Build the hufftree. */
  while (a->size > 1)
    {
      heap_insert(a, hufftree_link(heap_extract(a), heap_extract(a)));
    }

  return heap_extract(a);
}

/* hufftree_scan()
 * scan a huffman tree and build the bitstring array for encoding.
 */

void hufftree_scan(hufftree t, bitstring a, bitstring *bs)
{
  if ((NULL == t->left) && (NULL == t->right))
    {
      bs[hufftree_char(t)] = a;
    }
  else
    {
      /* Scan both subtrees. */
      hufftree_scan(t->left, bitstring_add(a, 0), bs);
      hufftree_scan(t->right, bitstring_add(a, 1), bs);

      /* Discard the unfinfished (non-leaf) bitstring. */
      bitstring_remove(a);
    }

  return;
}
