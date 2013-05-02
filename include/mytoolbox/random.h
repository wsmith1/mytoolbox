/*
 * include/linux/random.h
 *
 * Include file for the random number generator.
 */

#ifndef _MYTOOLBOX_RANDOM_H
#define _MYTOOLBOX_RANDOM_H

#include <inttypes.h>

struct rnd_state {
	uint32_t s1, s2, s3;
};

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 *	prandom32_s - seeded pseudo-random number generator.
 *	@state: pointer to state structure holding seeded state.
 *
 *	This is used for pseudo-randomness with no outside seeding.
 *	For more random results, use random32().
 */
uint32_t prandom32_s(struct rnd_state *);

/**
 *	srandom32_s - add entropy to pseudo random number generator
 *	@state: pointer to state structure holding seeded state.
 *	@seed: seed value
 *
 *	Add some additional seeding to the random32() pool.
 */
void srandom32_s(struct rnd_state *, uint32_t);

/*
 *	Generate some initially weak seeding values to allow
 *	to start the random32() engine.
 */
void random32_init_s(struct rnd_state *, uint32_t);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _MYTOOLBOX_RANDOM_H */
