#include <stdio.h>
#include <malloc.h>
#include "tree_superanchor.h"
#include "mytoolbox/bug.h"
#include "mytoolbox/cpu_cycles.h"
#include "mytoolbox/rbtree.h"
#include "mytoolbox/random.h"

const char *EDITION_NAME = "rbtree, super-anchor edition";

struct my_tree_node_sa_ll_s {
	struct rb_node_super_ll_s rbs;
	char unused1[TEST_RBTREE_ELEMENT_SIZE - sizeof(long) - sizeof(struct rb_node_super_ll_s)];
	long value;
};

static int test_tree_superanchor(void);

int main(void)
{
	fprintf(stdout, "Testing rbtree, %s\n", EDITION_NAME);
	test_tree_superanchor();
	return 0;
}

static int test_tree_superanchor(void)
{
	struct rnd_state rnd;
	struct rb_root tree_root = RB_ROOT;
	struct my_tree_node_sa_ll_s *datanodes;
	int i;
	int total_insert_count = 0;
	int total_find_count = 0;
	int total_remove_count = 0;
	uint32_t copy_tree_perf_count;
	uint64_t copy_tree_perf_ticks;
	BUILD_BUG_ON(sizeof(struct my_tree_node_sa_ll_s) != TEST_RBTREE_ELEMENT_SIZE);

	random32_init_s(&rnd, 100500);
	srandom32_s(&rnd, 42);

	fprintf(stdout, "Will insert %d nodes of size %lu\n", TEST_RBTREE_NODE_COUNT,
		(unsigned long)sizeof(struct my_tree_node_sa_ll_s));
	fflush(stdout);

	datanodes = calloc(TEST_RBTREE_NODE_COUNT, sizeof(*datanodes));
	if (!datanodes) {
		fprintf(stderr, "Not enough memory for data nodes\n");
		return -1;
	}

	for (i = 0; i < TEST_RBTREE_NODE_COUNT; i++) {
		uint32_t v;
		v = prandom32_s(&rnd);
		datanodes[i].rbs.k1 = (long)v;
		v = prandom32_s(&rnd);
		datanodes[i].rbs.k2 = (long)v;
		v = prandom32_s(&rnd);
		datanodes[i].value = (long)v;
	}

	for (i = 0; i < TEST_RBTREE_NODE_COUNT-TEST_RBTREE_NODE_STAT_COUNT; i++) {
		int ret;

		ret = tree_perf_insert(&tree_root,
			&datanodes[i].rbs);
		total_insert_count += ret;
	}

	tree_perf_count = 0;
	tree_perf_ticks = 0;
	for (i = TEST_RBTREE_NODE_COUNT-TEST_RBTREE_NODE_STAT_COUNT; i < TEST_RBTREE_NODE_COUNT; i++) {
		int ret;

		ret = tree_perf_insert(&tree_root,
			&datanodes[i].rbs);
		total_insert_count += ret;
	}
	copy_tree_perf_count = tree_perf_count;
	copy_tree_perf_ticks = tree_perf_ticks;

	fprintf(stdout, "Inserted %d nodes\n", total_insert_count);
	fprintf(stdout, "For %" PRIu32 " nodes: %" PRIu64 " total ticks, %" PRIu64 " per node\n",
		copy_tree_perf_count, copy_tree_perf_ticks,
		(copy_tree_perf_count != 0 ? copy_tree_perf_ticks / copy_tree_perf_count : 0));

	for (i = 0; i < TEST_RBTREE_NODE_COUNT-TEST_RBTREE_NODE_STAT_COUNT; i++) {
		const struct rb_node_super_ll_s *datanode_found_node;
		const struct my_tree_node_sa_ll_s *datanode_found;

		datanode_found_node = tree_perf_find_at(&tree_root, datanodes[i].rbs.k1, datanodes[i].rbs.k2);
		datanode_found = (datanode_found_node ? container_of_qual(datanode_found_node, struct my_tree_node_sa_ll_s, rbs, const) : NULL);

		if (datanode_found == &datanodes[i]) {
			total_find_count++;
		}
	}

	tree_perf_count = 0;
	tree_perf_ticks = 0;
	for (i = TEST_RBTREE_NODE_COUNT-TEST_RBTREE_NODE_STAT_COUNT; i < TEST_RBTREE_NODE_COUNT; i++) {
		const struct rb_node_super_ll_s *datanode_found_node;
		const struct my_tree_node_sa_ll_s *datanode_found;

		datanode_found_node = tree_perf_find_at(&tree_root, datanodes[i].rbs.k1, datanodes[i].rbs.k2);
		datanode_found = (datanode_found_node ? container_of_qual(datanode_found_node, struct my_tree_node_sa_ll_s, rbs, const) : NULL);

		if (datanode_found == &datanodes[i]) {
			total_find_count++;
		}
	}
	copy_tree_perf_count = tree_perf_count;
	copy_tree_perf_ticks = tree_perf_ticks;

	fprintf(stdout, "Found %d nodes\n", total_find_count);
	fprintf(stdout, "For %" PRIu32 " nodes: %" PRIu64 " total ticks, %" PRIu64 " per node\n",
		copy_tree_perf_count, copy_tree_perf_ticks,
		(copy_tree_perf_count != 0 ? copy_tree_perf_ticks / copy_tree_perf_count : 0));

	tree_perf_count = 0;
	tree_perf_ticks = 0;
	for (i = 0; i < TEST_RBTREE_NODE_STAT_COUNT; i++) {
		struct rb_node_super_ll_s *datanode_found_node;
		struct my_tree_node_sa_ll_s *datanode_found;

		datanode_found_node = tree_perf_remove_at(&tree_root, datanodes[i].rbs.k1, datanodes[i].rbs.k2);
		datanode_found = (datanode_found_node ? container_of(datanode_found_node, struct my_tree_node_sa_ll_s, rbs) : NULL);

		if (datanode_found == &datanodes[i]) {
			total_remove_count++;
		}
	}
	copy_tree_perf_count = tree_perf_count;
	copy_tree_perf_ticks = tree_perf_ticks;
	for (i = TEST_RBTREE_NODE_STAT_COUNT; i < TEST_RBTREE_NODE_COUNT; i++) {
		struct rb_node_super_ll_s *datanode_found_node;
		struct my_tree_node_sa_ll_s *datanode_found;

		datanode_found_node = tree_perf_remove_at(&tree_root, datanodes[i].rbs.k1, datanodes[i].rbs.k2);
		datanode_found = (datanode_found_node ? container_of(datanode_found_node, struct my_tree_node_sa_ll_s, rbs) : NULL);

		if (datanode_found == &datanodes[i]) {
			total_remove_count++;
		}
	}

	fprintf(stdout, "Removed %d nodes\n", total_remove_count);
	fprintf(stdout, "For %" PRIu32 " nodes: %" PRIu64 " total ticks, %" PRIu64 " per node\n",
		copy_tree_perf_count, copy_tree_perf_ticks,
		(copy_tree_perf_count != 0 ? copy_tree_perf_ticks / copy_tree_perf_count : 0));

	free(datanodes);
	return 0;
}


