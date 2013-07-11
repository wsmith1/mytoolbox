#ifndef __test_rbtree_perf_tree_callbacks1_h
#define __test_rbtree_perf_tree_callbacks1_h 1

#include <inttypes.h>
#include "tree_config.h"


struct rb_root;
struct rb_node;

typedef int (*tree_perf_compar_f)(const void *_key1, const struct rb_node *_node2);

extern uint32_t tree_perf_count;
extern uint64_t tree_perf_ticks;

int tree_perf_insert(struct rb_root *root, const void *_new_key, struct rb_node *_new_node, tree_perf_compar_f compar_func);
struct rb_node *tree_perf_find_at(const struct rb_root *root, const void *_key, tree_perf_compar_f compar_func);
struct rb_node *tree_perf_remove_at(struct rb_root *root, const void *_key, tree_perf_compar_f compar_func);

#endif /* __test_rbtree_perf_tree_callbacks1_h */

