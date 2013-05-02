#include <stdio.h>
#include <inttypes.h>
#include "mytoolbox/random.h"
#include "mytoolbox/cpu_cycles.h"

#define LOOP_CNT 10
#define LOOP_CNT_IN 4

static int demo_random(void)
{
	int i, j;
	uint32_t d1;
	struct rnd_state state;

	fprintf(stdout, "Pseudo-random number generator demo\n");

	d1 = get_cpu_cycles_32();
	random32_init_s(&state, d1);

	d1 = get_cpu_cycles_32();
	srandom32_s(&state, d1);

	for (i = 0; i < LOOP_CNT; i++) {
		for (j = 0; j < LOOP_CNT_IN; j++) {
			uint32_t r;
			r = prandom32_s(&state);
			d1 = get_cpu_cycles_32();
			srandom32_s(&state, d1);
			fprintf(stdout, "  %10lu", (unsigned long)r);
		}
		fprintf(stdout, "\n");
	}
	return 0;
}

int main(void)
{
	demo_random();
	return 0;
}


