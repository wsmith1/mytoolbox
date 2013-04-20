#include <stdio.h>
#include <inttypes.h>
#include "mytoolbox/rbtree_test.h"

static int test_rbtree(void)
{

	fprintf(stderr, "Red-black tree code test\n");

	rbtree_test();

	return 0;
}

int main(void)
{
	test_rbtree();
	return 0;
}



