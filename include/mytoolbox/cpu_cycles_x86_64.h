#ifndef __MYTOOLBOX_CPU_CYCLES_H
#error "Please don't include 'mytoolbox/cpu_cycles_x86_64.h' directly, include 'mytoolbox/cpu_cycles.h' instead."
#endif /* __MYTOOLBOX_CPU_CYCLES_H */

static __always_inline uint64_t get_cpu_cycles_64(void)
{
	uint32_t lo, hi;
	uint64_t c;
	/* We cannot use "=A", since this would use %rax on x86_64,
	   and return only the lower 32bits of the TSC */
	__asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
	c = ((uint64_t)hi) << 32 | (uint64_t)lo;
	return c;
}

static __always_inline uint32_t get_cpu_cycles_32(void)
{
	uint32_t lo;
	/* We cannot use "=A", since this would use %rax on x86_64,
	   and return only the lower 32bits of the TSC */
	__asm__ __volatile__ ("rdtsc" : "=a" (lo));
	return lo;
}

