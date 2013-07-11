#include <stdio.h>
#include <malloc.h>
#include "tree_callbacks1.h"
#include "mytoolbox/bug.h"
#include "mytoolbox/cpu_cycles.h"
#include "mytoolbox/rbtree.h"
#include "mytoolbox/random.h"

const char *EDITION_NAME = "rbtree, callbacks edition 1";

struct my_key_struct_s {
	long k1;
	long k2;
};

struct my_tree_node_c1_ll_s {
	long k1;
	long k2;
	struct rb_node rb;
	char unused1[TEST_RBTREE_ELEMENT_SIZE - 3 * sizeof(long) - sizeof(struct rb_node)];
	long value;
};

static int test_tree_callbacks1(void);

int main(void)
{
	fprintf(stdout, "Testing rbtree, %s\n", EDITION_NAME);
	test_tree_callbacks1();
	return 0;
}

static int my_tree_compar_func(const void *_key1, const struct rb_node *_node2)
{
	const struct my_key_struct_s * const key1 = (const struct my_key_struct_s *)_key1;
	const struct my_tree_node_c1_ll_s *node2 = rb_entry_qual(_node2, struct my_tree_node_c1_ll_s, rb, const);
	if (key1->k1 < node2->k1) {
		return -1;
	}
	else if (key1->k1 > node2->k1) {
		return 1;
	}
	else {
		if (key1->k2 < node2->k2) {
			return -1;
		}
		else if (key1->k2 > node2->k2) {
			return 1;
		}
		else {
			return 0;
		}
	}
}

static int test_tree_callbacks1(void)
{
	struct rnd_state rnd;
	struct rb_root tree_root = RB_ROOT;
	struct my_tree_node_c1_ll_s *datanodes;
	int i;
	int total_insert_count = 0;
	int total_find_count = 0;
	int total_remove_count = 0;
	uint32_t copy_tree_perf_count;
	uint64_t copy_tree_perf_ticks;
	BUILD_BUG_ON(sizeof(struct my_tree_node_c1_ll_s) != TEST_RBTREE_ELEMENT_SIZE);

	random32_init_s(&rnd, 100500);
	srandom32_s(&rnd, 42);

	fprintf(stdout, "Will insert %d nodes of size %lu\n", TEST_RBTREE_NODE_COUNT,
		(unsigned long)sizeof(struct my_tree_node_c1_ll_s));
	fflush(stdout);

	datanodes = calloc(TEST_RBTREE_NODE_COUNT, sizeof(*datanodes));
	if (!datanodes) {
		fprintf(stderr, "Not enough memory for data nodes\n");
		return -1;
	}

	for (i = 0; i < TEST_RBTREE_NODE_COUNT; i++) {
		uint32_t v;
		v = prandom32_s(&rnd);
		datanodes[i].k1 = (long)v;
		v = prandom32_s(&rnd);
		datanodes[i].k2 = (long)v;
		v = prandom32_s(&rnd);
		datanodes[i].value = (long)v;
	}

	for (i = 0; i < TEST_RBTREE_NODE_COUNT-TEST_RBTREE_NODE_STAT_COUNT; i++) {
		int ret;
		struct my_key_struct_s key_struct = {.k1 = datanodes[i].k1, .k2 = datanodes[i].k2};
		ret = tree_perf_insert(&tree_root, &key_struct,
			&datanodes[i].rb, my_tree_compar_func);
		total_insert_count += ret;
	}

	tree_perf_count = 0;
	tree_perf_ticks = 0;
	for (i = TEST_RBTREE_NODE_COUNT-TEST_RBTREE_NODE_STAT_COUNT; i < TEST_RBTREE_NODE_COUNT; i++) {
		int ret;
		struct my_key_struct_s key_struct = {.k1 = datanodes[i].k1, .k2 = datanodes[i].k2};
		ret = tree_perf_insert(&tree_root, &key_struct,
			&datanodes[i].rb, my_tree_compar_func);
		total_insert_count += ret;
	}
	copy_tree_perf_count = tree_perf_count;
	copy_tree_perf_ticks = tree_perf_ticks;

	fprintf(stdout, "Inserted %d nodes\n", total_insert_count);
	fprintf(stdout, "For %" PRIu32 " nodes: %" PRIu64 " total ticks, %" PRIu64 " per node\n",
		copy_tree_perf_count, copy_tree_perf_ticks,
		(copy_tree_perf_count != 0 ? copy_tree_perf_ticks / copy_tree_perf_count : 0));

	for (i = 0; i < TEST_RBTREE_NODE_COUNT-TEST_RBTREE_NODE_STAT_COUNT; i++) {
		const struct rb_node *datanode_found_node;
		const struct my_tree_node_c1_ll_s *datanode_found;
		struct my_key_struct_s key_struct = {.k1 = datanodes[i].k1, .k2 = datanodes[i].k2};

		datanode_found_node = tree_perf_find_at(&tree_root, &key_struct, my_tree_compar_func);
		datanode_found = (datanode_found_node ? container_of_qual(datanode_found_node, struct my_tree_node_c1_ll_s, rb, const) : NULL);

		if (datanode_found == &datanodes[i]) {
			total_find_count++;
		}
	}

	tree_perf_count = 0;
	tree_perf_ticks = 0;
	for (i = TEST_RBTREE_NODE_COUNT-TEST_RBTREE_NODE_STAT_COUNT; i < TEST_RBTREE_NODE_COUNT; i++) {
		const struct rb_node *datanode_found_node;
		const struct my_tree_node_c1_ll_s *datanode_found;
		struct my_key_struct_s key_struct = {.k1 = datanodes[i].k1, .k2 = datanodes[i].k2};

		datanode_found_node = tree_perf_find_at(&tree_root, &key_struct, my_tree_compar_func);
		datanode_found = (datanode_found_node ? container_of_qual(datanode_found_node, struct my_tree_node_c1_ll_s, rb, const) : NULL);

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
		struct rb_node *datanode_found_node;
		struct my_tree_node_c1_ll_s *datanode_found;
		struct my_key_struct_s key_struct = {.k1 = datanodes[i].k1, .k2 = datanodes[i].k2};

		datanode_found_node = tree_perf_remove_at(&tree_root, &key_struct, my_tree_compar_func);
		datanode_found = (datanode_found_node ? container_of(datanode_found_node, struct my_tree_node_c1_ll_s, rb) : NULL);

		if (datanode_found == &datanodes[i]) {
			total_remove_count++;
		}
	}
	copy_tree_perf_count = tree_perf_count;
	copy_tree_perf_ticks = tree_perf_ticks;
	for (i = TEST_RBTREE_NODE_STAT_COUNT; i < TEST_RBTREE_NODE_COUNT; i++) {
		struct rb_node *datanode_found_node;
		struct my_tree_node_c1_ll_s *datanode_found;
		struct my_key_struct_s key_struct = {.k1 = datanodes[i].k1, .k2 = datanodes[i].k2};

		datanode_found_node = tree_perf_remove_at(&tree_root, &key_struct, my_tree_compar_func);
		datanode_found = (datanode_found_node ? container_of(datanode_found_node, struct my_tree_node_c1_ll_s, rb) : NULL);

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


