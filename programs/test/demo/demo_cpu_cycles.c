#include <stdio.h>
#include <inttypes.h>
#include "mytoolbox/random.h"
#include "mytoolbox/cpu_cycles.h"

#define LOOP_CNT 10

static int demo_cpu_cycles(void)
{
	int i;
	uint64_t q1, q2, qdiff;
	uint32_t d1, d2, ddiff;
	uint32_t r, rsum = 0;
	struct rnd_state state;

	fprintf(stdout, "CPU cycles reading demo\n");

	d1 = get_cpu_cycles_32();
	d2 = get_cpu_cycles_32();

	random32_init_s(&state, d1);
	srandom32_s(&state, d2);

	fprintf(stdout, "  Using get_cpu_cycles_32()\n");
	for (i = 0; i < LOOP_CNT; i++) {
		d1 = get_cpu_cycles_32();
		r = prandom32_s(&state);
		rsum = rsum + r;
		r = prandom32_s(&state);
		rsum = rsum + r;
		r = prandom32_s(&state);
		rsum = rsum + r;
		d2 = get_cpu_cycles_32();
		ddiff = d2 - d1;
		fprintf(stdout, "    Cycles %d: %lu (%#lx to %#lx)\n", i,
			(unsigned long)ddiff, (unsigned long)d1,
			(unsigned long)d2);
	}

	fprintf(stdout, "  Using get_cpu_cycles_64()\n");
	for (i = 0; i < LOOP_CNT; i++) {
		q1 = get_cpu_cycles_64();
		r = prandom32_s(&state);
		rsum = rsum + r;
		r = prandom32_s(&state);
		rsum = rsum + r;
		r = prandom32_s(&state);
		rsum = rsum + r;
		q2 = get_cpu_cycles_64();
		qdiff = q2 - q1;
		fprintf(stdout, "    Cycles %d: %llu (%#llx to %#llx)\n", i,
			(unsigned long long)qdiff, (unsigned long long)q1,
			(unsigned long long)q2);
	}

	fprintf(stdout, "  Sum of pseudo-random numbers: %lu\n", (unsigned long)rsum);

	return 0;
}

int main(void)
{
	demo_cpu_cycles();
	return 0;
}

