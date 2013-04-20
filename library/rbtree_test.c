#include <stdio.h>
#include <inttypes.h>
#include <errno.h>
#include "mytoolbox/bug-warn.h"
#include "mytoolbox/cpu_cycles.h"
#include "mytoolbox/random.h"
#include "mytoolbox/rbtree.h"
#include "mytoolbox/rbtree_test.h"

#define NODES       100
#define PERF_LOOPS  100000
#define CHECK_LOOPS 100

struct test_node {
	struct rb_node rb;
	uint32_t key;

	/* following fields used for testing augmented rbtree functionality */
	uint32_t val;
	uint32_t augmented;
};

static void insert(struct test_node *node, struct rb_root *root)
{
	struct rb_node **new = &root->rb_node, *parent = NULL;
	uint32_t key = node->key;

	while (*new) {
		uint32_t parent_key;
		parent = *new;
		parent_key = rb_entry(parent, struct test_node, rb)->key;
		if (key < parent_key) {
			new = &parent->rb_left;
		}
		else if (key > parent_key) {
			new = &parent->rb_right;
		}
		else {
			/* have to do it for now, FIXME later */
			new = &parent->rb_right;
			WARN_ONCE(1, "duplicate key %lu\n", (unsigned long)key);
		}
	}

	rb_link_node(&node->rb, parent, new);
	rb_insert_color(&node->rb, root);
}

static inline void erase(struct test_node *node, struct rb_root *root)
{
	rb_erase(&node->rb, root);
}

static inline uint32_t augment_recompute(struct test_node *node)
{
	uint32_t max = node->val, child_augmented;
	if (node->rb.rb_left) {
		child_augmented = rb_entry(node->rb.rb_left, struct test_node,
					   rb)->augmented;
		if (max < child_augmented)
			max = child_augmented;
	}
	if (node->rb.rb_right) {
		child_augmented = rb_entry(node->rb.rb_right, struct test_node,
					   rb)->augmented;
		if (max < child_augmented)
			max = child_augmented;
	}
	return max;
}

static void augment_callback(struct rb_node *node, void *data)
{
	struct test_node *node1 = rb_entry(node, struct test_node, rb);
	uninitialized_var(data);
	node1->augmented = augment_recompute(node1);
}

static void insert_augmented(struct test_node *node, struct rb_root *root)
{
	struct rb_node **new = &root->rb_node, *rb_parent = NULL;
	uint32_t key = node->key;
	uint32_t val = node->val;
	struct test_node *parent;

	while (*new) {
		rb_parent = *new;
		parent = rb_entry(rb_parent, struct test_node, rb);
		if (parent->augmented < val)
			parent->augmented = val;
		if (key < parent->key) {
			new = &parent->rb.rb_left;
		}
		else if (key > parent->key) {
			new = &parent->rb.rb_right;
		}
		else {
			new = &parent->rb.rb_right;
			WARN_ONCE(1, "duplicate key %lu\n", (unsigned long)key);
		}
	}

	node->augmented = val;
	rb_link_node(&node->rb, rb_parent, new);
	rb_insert_color(&node->rb, root);
	rb_augment_insert(&node->rb, augment_callback, NULL);
}

static void erase_augmented(struct test_node *node, struct rb_root *root)
{
	struct rb_node *deepest;
	deepest = rb_augment_erase_begin(&node->rb);
	rb_erase(&node->rb, root);
	rb_augment_erase_end(deepest, augment_callback, NULL);
}

static struct rb_root root = RB_ROOT;
static struct test_node nodes[NODES];

static struct rnd_state rnd;


static void init(void)
{
	int i;
	for (i = 0; i < NODES; i++) {
		nodes[i].key = prandom32_s(&rnd);
		nodes[i].val = prandom32_s(&rnd);
	}
}

static int is_red(struct rb_node *rb)
{
	return !(rb->rb_parent_color & 1);
}

static int black_path_count(struct rb_node *rb)
{
	int count;
	for (count = 0; rb; rb = rb_parent(rb))
		count += !is_red(rb);
	return count;
}

static void check(int nr_nodes)
{
	struct rb_node *rb;
	int count = 0;
	int blacks = 0;
	uint32_t prev_key = 0;

	for (rb = rb_first(&root); rb; rb = rb_next(rb)) {
		struct test_node *node = rb_entry(rb, struct test_node, rb);
		WARN_ON_ONCE(node->key < prev_key);
		WARN_ON_ONCE(is_red(rb) &&
			     (!rb_parent(rb) || is_red(rb_parent(rb))));
		if (!count)
			blacks = black_path_count(rb);
		else
			WARN_ON_ONCE((!rb->rb_left || !rb->rb_right) &&
				     blacks != black_path_count(rb));
		prev_key = node->key;
		count++;
	}
	WARN_ON_ONCE(count != nr_nodes);
}

static void check_augmented(int nr_nodes)
{
	struct rb_node *rb;

	check(nr_nodes);
	for (rb = rb_first(&root); rb; rb = rb_next(rb)) {
		struct test_node *node = rb_entry(rb, struct test_node, rb);
		WARN_ON_ONCE(node->augmented != augment_recompute(node));
	}
}

int rbtree_test(void)
{
	int i, j;
	uint64_t time1, time2, time;

	fprintf(stderr, "rbtree testing");

	random32_init_s(&rnd, 3141592653UL);
	time1 = get_cpu_cycles_64();
	srandom32_s(&rnd, (uint32_t)time1);

	init();

	time1 = get_cpu_cycles_64();

	for (i = 0; i < PERF_LOOPS; i++) {
		for (j = 0; j < NODES; j++)
			insert(nodes + j, &root);
		for (j = 0; j < NODES; j++)
			erase(nodes + j, &root);
	}

	time2 = get_cpu_cycles_64();
	time = time2 - time1;

	time = (time / PERF_LOOPS);
	fprintf(stderr, " -> %llu cycles\n", (unsigned long long)time);

	for (i = 0; i < CHECK_LOOPS; i++) {
		init();
		for (j = 0; j < NODES; j++) {
			check(j);
			insert(nodes + j, &root);
		}
		for (j = 0; j < NODES; j++) {
			check(NODES - j);
			erase(nodes + j, &root);
		}
		check(0);
	}

	fprintf(stderr, "augmented rbtree testing");

	init();

	time1 = get_cpu_cycles_64();

	for (i = 0; i < PERF_LOOPS; i++) {
		for (j = 0; j < NODES; j++)
			insert_augmented(nodes + j, &root);
		for (j = 0; j < NODES; j++)
			erase_augmented(nodes + j, &root);
	}

	time2 = get_cpu_cycles_64();
	time = time2 - time1;

	time = (time / PERF_LOOPS);
	fprintf(stderr, " -> %llu cycles\n", (unsigned long long)time);

	for (i = 0; i < CHECK_LOOPS; i++) {
		init();
		for (j = 0; j < NODES; j++) {
			check_augmented(j);
			insert_augmented(nodes + j, &root);
		}
		for (j = 0; j < NODES; j++) {
			check_augmented(NODES - j);
			erase_augmented(nodes + j, &root);
		}
		check_augmented(0);
	}

	return -EAGAIN; /* Fail will directly unload the module */
}

