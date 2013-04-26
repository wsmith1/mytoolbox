#ifndef __programs_test_rbtree_perf_superanchor3_h
#define __programs_test_rbtree_perf_superanchor3_h 1

#include <inttypes.h>
#include "mytoolbox/rbtree.h"

struct rb_root;

extern int tree_perf_ticks_enable;
extern uint32_t tree_perf_insert_count;
extern uint64_t tree_perf_insert_ticks;
extern uint32_t tree_perf_find_count;
extern uint64_t tree_perf_find_ticks;
extern uint32_t tree_perf_remove_count;
extern uint64_t tree_perf_remove_ticks;

struct rb_node_super_ll
{
	long k1;
	long k2;
	struct rb_node rb;
};

typedef int (*tree_perf_compar_f)(long k1, long k2, const struct rb_node_super_ll *node_super_ll);

int tree_perf_insert(struct rb_root *root, struct rb_node_super_ll *node_super_ll,
		tree_perf_compar_f cmp_func);
const struct rb_node_super_ll *tree_perf_find_at(struct rb_root *root, long k1, long k2,
		tree_perf_compar_f cmp_func);
struct rb_node_super_ll *tree_perf_remove_at(struct rb_root *root, long k1, long k2,
		tree_perf_compar_f cmp_func);

#endif /* __programs_test_rbtree_perf_superanchor3_h */

