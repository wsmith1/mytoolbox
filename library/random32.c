/*
  This is a maximally equidistributed combined Tausworthe generator
  based on code from GNU Scientific Library 1.5 (30 Jun 2004)

   x_n = (s1_n ^ s2_n ^ s3_n)

   s1_{n+1} = (((s1_n & 4294967294) <<12) ^ (((s1_n <<13) ^ s1_n) >>19))
   s2_{n+1} = (((s2_n & 4294967288) << 4) ^ (((s2_n << 2) ^ s2_n) >>25))
   s3_{n+1} = (((s3_n & 4294967280) <<17) ^ (((s3_n << 3) ^ s3_n) >>11))

   The period of this generator is about 2^88.

   From: P. L'Ecuyer, "Maximally Equidistributed Combined Tausworthe
   Generators", Mathematics of Computation, 65, 213 (1996), 203--213.

   This is available on the net from L'Ecuyer's home page,

   http://www.iro.umontreal.ca/~lecuyer/myftp/papers/tausme.ps
   ftp://ftp.iro.umontreal.ca/pub/simulation/lecuyer/papers/tausme.ps

   There is an erratum in the paper "Tables of Maximally
   Equidistributed Combined LFSR Generators", Mathematics of
   Computation, 68, 225 (1999), 261--269:
   http://www.iro.umontreal.ca/~lecuyer/myftp/papers/tausme2.ps

        ... the k_j most significant bits of z_j must be non-
        zero, for each j. (Note: this restriction also applies to the
        computer code given in [4], but was mistakenly not mentioned in
        that paper.)

   This affects the seeding procedure by imposing the requirement
   s1 > 1, s2 > 7, s3 > 15.

*/

#include <inttypes.h>
#include "mytoolbox/random.h"

#define TAUSWORTHE(s,a,b,c,d) ((s&c)<<d) ^ (((s <<a) ^ s)>>b)

/**
 *	prandom32_s - seeded pseudo-random number generator.
 *	@state: pointer to state structure holding seeded state.
 *
 *	This is used for pseudo-randomness with no outside seeding.
 *	For more random results, use random32().
 */
uint32_t prandom32_s(struct rnd_state *state)
{

	state->s1 = (uint32_t)(TAUSWORTHE(state->s1, 13, 19, 4294967294UL, 12));
	state->s2 = (uint32_t)(TAUSWORTHE(state->s2, 2, 25, 4294967288UL, 4));
	state->s3 = (uint32_t)(TAUSWORTHE(state->s3, 3, 11, 4294967280UL, 17));

	return (state->s1 ^ state->s2 ^ state->s3);
}

/*
 * Handle minimum values for seeds
 */
static inline uint32_t __seed(uint32_t x, uint32_t m)
{
	return (x < m) ? x + m : x;
}

/**
 *	srandom32_s - add entropy to pseudo random number generator
 *	@state: pointer to state structure holding seeded state.
 *	@seed: seed value
 *
 *	Add some additional seeding to the random32() pool.
 */
void srandom32_s(struct rnd_state *state, uint32_t entropy)
{
	state->s1 = __seed(state->s1 ^ entropy, 1);
}


#define LCG(x)	((x) * 69069)	/* super-duper LCG */

/*
 *	Generate some initially weak seeding values to allow
 *	to start the random32() engine.
 */
void random32_init_s(struct rnd_state *state, uint32_t entropy)
{
	state->s1 = __seed(LCG(entropy), 1);
	state->s2 = __seed(LCG(state->s1), 7);
	state->s3 = __seed(LCG(state->s2), 15);

	/* "warm it up" */
	prandom32_s(state);
	prandom32_s(state);
	prandom32_s(state);
	prandom32_s(state);
	prandom32_s(state);
	prandom32_s(state);

	/* "warm it up even more" */
	prandom32_s(state);
	prandom32_s(state);
	prandom32_s(state);
	prandom32_s(state);
	prandom32_s(state);
	prandom32_s(state);
}

