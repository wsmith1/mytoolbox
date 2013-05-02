#include <stdio.h>
#include <inttypes.h>
#include "mytoolbox/rbtree_test.h"

static int demo_rbtree(void)
{

	fprintf(stderr, "Red-black tree code demo\n");

	rbtree_test();

	return 0;
}

int main(void)
{
	demo_rbtree();
	return 0;
}



