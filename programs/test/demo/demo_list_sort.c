#include <stdio.h>
#include <inttypes.h>
#include "mytoolbox/list_sort.h"
#include "mytoolbox/cpu_cycles.h"

static int demo_list_sort(void)
{
	uint64_t q1, q2, qdiff;

	fprintf(stderr, "Linked list sorting demo\n");

	q1 = get_cpu_cycles_64();
	list_sort_test();
	q2 = get_cpu_cycles_64();
	qdiff = q2 - q1;
	fprintf(stderr, "List sort completed, %llu cycles\n",
		(unsigned long long)qdiff);
	return 0;
}

int main(void)
{
	demo_list_sort();
	return 0;
}

