#ifndef __test_rbtree_perf_tree_superanchor_h
#define __test_rbtree_perf_tree_superanchor_h 1

#include <inttypes.h>
#include "mytoolbox/rbtree.h"
#include "tree_config.h"


struct rb_root;

extern uint32_t tree_perf_count;
extern uint64_t tree_perf_ticks;

struct rb_node_super_ll_s {
	long k1;
	long k2;
	struct rb_node rb;
};

int tree_perf_insert(struct rb_root *root, struct rb_node_super_ll_s *rb_node_super);
struct rb_node_super_ll_s *tree_perf_find_at(const struct rb_root *root, long k1, long k2);
struct rb_node_super_ll_s *tree_perf_remove_at(struct rb_root *root, long k1, long k2);

#endif /* __test_rbtree_perf_tree_superanchor_h */

