#ifndef __test_rbtree_perf_tree_config_h
#define __test_rbtree_perf_tree_config_h 1

#define TEST_RBTREE_TOTAL_ELEM_SIZE 1024000000
#define TEST_RBTREE_ELEMENT_SIZE (1024+0)
#define TEST_RBTREE_NODE_COUNT (TEST_RBTREE_TOTAL_ELEM_SIZE/TEST_RBTREE_ELEMENT_SIZE)
#define TEST_RBTREE_NODE_STAT_COUNT (TEST_RBTREE_NODE_COUNT/8)

#endif /* __test_rbtree_perf_tree_config_h */
