#include <stdio.h>
#include <inttypes.h>
#include <malloc.h>
#include "mytoolbox/cpu_cycles.h"
#include "mytoolbox/rbtree.h"
#include "mytoolbox/random.h"
#include "rbtree_perf_student2.h"

struct tree_key_s {
	long k1;
	long k2;
};

struct tree_data_s {
	struct tree_key_s key;
	char unused1[256];
	long value;
};

/* Total number of nodes to insert or remove */
#define NODE_COUNT 1000000
/* Number of nodes over which to collect statistics */
#define NODE_STAT_COUNT 100000

static int rbtree_perf_compar(const void *key, const void *data)
{
	const struct tree_key_s * const kp = key;
	const struct tree_data_s *const da = data;
	if (kp->k1 < da->key.k1) {
		return -1;
	}
	else if (kp->k1 > da->key.k1) {
		return 1;
	}
	else {
		if (kp->k2 < da->key.k2) {
			return -1;
		}
		else if (kp->k2 > da->key.k2) {
			return 1;
		}
		else {
			return 0;
		}
	}
}

static int rbtree_perf_student2_test(void)
{
	struct rnd_state rnd;
	struct tree_data_s *datanodes;
	struct tree_key_s datanode_key;
	struct rb_root tree_root = RB_ROOT;
	int i;
	int total_insert_count = 0;
	int total_find_count = 0;
	int total_remove_count = 0;

	random32_init_s(&rnd, 100500);
	srandom32_s(&rnd, 42);
	datanodes = calloc(NODE_COUNT, sizeof(*datanodes));
	if (!datanodes) {
		fprintf(stderr, "Not enough memory for data nodes\n");
		return -1;
	}

	for (i = 0; i < NODE_COUNT; i++) {
		uint32_t v;
		v = prandom32_s(&rnd);
		datanodes[i].key.k1 = (long)v;
		v = prandom32_s(&rnd);
		datanodes[i].key.k2 = (long)v;
		v = prandom32_s(&rnd);
		datanodes[i].value = (long)v;
	}

	for (i = 0; i < NODE_COUNT-NODE_STAT_COUNT; i++) {
		int ret;
		datanode_key = datanodes[i].key;

		ret = tree_perf_insert(&tree_root, &datanode_key,
			&datanodes[i], rbtree_perf_compar);
		total_insert_count += ret;
	}
	tree_perf_ticks_enable = 1;
	for (i = NODE_COUNT-NODE_STAT_COUNT; i < NODE_COUNT; i++) {
		int ret;
		datanode_key = datanodes[i].key;

		ret = tree_perf_insert(&tree_root, &datanode_key,
			&datanodes[i], rbtree_perf_compar);
		total_insert_count += ret;
	}
	tree_perf_ticks_enable = 0;

	fprintf(stdout, "Inserted %d nodes\n", total_insert_count);
	fprintf(stdout, "Ticks: %" PRIu64 " total, %" PRIu64 " per node for %" PRIu32 " nodes\n",
		tree_perf_insert_ticks, tree_perf_insert_ticks/tree_perf_insert_count,
		tree_perf_insert_count);

	for (i = 0; i < NODE_COUNT-NODE_STAT_COUNT; i++) {
		const struct tree_data_s *datanode_found;
		datanode_key = datanodes[i].key;

		datanode_found = tree_perf_find_at(&tree_root, &datanode_key,
			rbtree_perf_compar);
		if (datanode_found == &datanodes[i]) {
			total_find_count++;
		}
	}
	tree_perf_ticks_enable = 1;
	for (i = NODE_COUNT-NODE_STAT_COUNT; i < NODE_COUNT; i++) {
		const struct tree_data_s *datanode_found;
		datanode_key = datanodes[i].key;

		datanode_found = tree_perf_find_at(&tree_root, &datanode_key,
			rbtree_perf_compar);
		if (datanode_found == &datanodes[i]) {
			total_find_count++;
		}
	}
	tree_perf_ticks_enable = 0;

	fprintf(stdout, "Found %d nodes\n", total_find_count);
	fprintf(stdout, "Ticks: %" PRIu64 " total, %" PRIu64 " per node for %" PRIu32 " nodes\n",
		tree_perf_find_ticks, tree_perf_find_ticks/tree_perf_find_count,
		tree_perf_find_count);

	tree_perf_ticks_enable = 1;
	for (i = 0; i < NODE_STAT_COUNT; i++) {
		datanode_key = datanodes[i].key;

		struct tree_data_s *datanode_found = tree_perf_remove_at(&tree_root, &datanode_key,
			rbtree_perf_compar);
		if (datanode_found == &datanodes[i]) {
			total_remove_count++;
		}
	}
	tree_perf_ticks_enable = 0;

	for (i = NODE_STAT_COUNT; i < NODE_COUNT; i++) {
		datanode_key = datanodes[i].key;

		struct tree_data_s *datanode_found = tree_perf_remove_at(&tree_root, &datanode_key,
			rbtree_perf_compar);
		if (datanode_found == &datanodes[i]) {
			total_remove_count++;
		}
	}

	fprintf(stdout, "Removed %d nodes\n", total_remove_count);
	fprintf(stdout, "Ticks: %" PRIu64 " total, %" PRIu64 " per node for %" PRIu32 " nodes\n",
		tree_perf_remove_ticks, tree_perf_remove_ticks/tree_perf_remove_count,
		tree_perf_remove_count);

	free(datanodes);
	return 0;
}

int main(void)
{
	fprintf(stdout, "Testing rbtree, student edition 2\n");
	rbtree_perf_student2_test();
	return 0;
}

