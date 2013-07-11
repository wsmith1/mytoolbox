#ifndef __test_rbtree_perf_tree_embedded_h
#define __test_rbtree_perf_tree_embedded_h 1

#include <inttypes.h>
#include "mytoolbox/rbtree.h"
#include "tree_config.h"


struct rb_root;

extern uint32_t tree_perf_count;
extern uint64_t tree_perf_ticks;

struct my_tree_node_ll_s {
	long k1;
	long k2;
	struct rb_node rb;
	char unused1[TEST_RBTREE_ELEMENT_SIZE - 3 * sizeof(long) - sizeof(struct rb_node)];
	long value;
};

int tree_perf_insert(struct rb_root *root, struct my_tree_node_ll_s *my_node);
struct my_tree_node_ll_s *tree_perf_find_at(const struct rb_root *root, long k1, long k2);
struct my_tree_node_ll_s *tree_perf_remove_at(struct rb_root *root, long k1, long k2);

#endif /* __test_rbtree_perf_tree_embedded_h */

