#include <inttypes.h>
#include <malloc.h>
#include "mytoolbox/cpu_cycles.h"
#include "mytoolbox/rbtree.h"
#include "rbtree_perf_superanchor3.h"

int tree_perf_ticks_enable = 0;
uint32_t tree_perf_insert_count = 0;
uint64_t tree_perf_insert_ticks = 0;
uint32_t tree_perf_find_count = 0;
uint64_t tree_perf_find_ticks = 0;
uint32_t tree_perf_remove_count = 0;
uint64_t tree_perf_remove_ticks = 0;

int tree_perf_insert(struct rb_root *root, struct rb_node_super_ll *node_super_ll,
		tree_perf_compar_f cmp_func)
{
	uint64_t c1, c2;
	struct rb_node **_new;
	struct rb_node *parent = NULL;

	c1 = get_cpu_cycles_64();
	_new = &root->rb_node;
	while ((*_new) != NULL) {
		const struct rb_node_super_ll *parent_super_ll;
		int cmp_ret;

		parent = (*_new);
		parent_super_ll = rb_entry_qual(parent, struct rb_node_super_ll, rb, const);

		cmp_ret = cmp_func(node_super_ll->k1, node_super_ll->k2, parent_super_ll);
		if (cmp_ret < 0) {
			_new = &parent->rb_left;
		}
		else if (cmp_ret > 0) {
			_new = &parent->rb_right;
		}
		else {
			return 0;
		}
	}

	rb_link_node(&node_super_ll->rb, parent, _new);
	rb_insert_color(&node_super_ll->rb, root);
	c2 = get_cpu_cycles_64();
	if (tree_perf_ticks_enable) {
		c2 = c2 - c1;
		tree_perf_insert_count++;
		tree_perf_insert_ticks += c2;
	}
	return 1;
}

const struct rb_node_super_ll *tree_perf_find_at(struct rb_root *root, long k1, long k2,
		tree_perf_compar_f cmp_func)
{
	struct rb_node *node;
	const struct rb_node_super_ll *node_super_ll_found = NULL;

	uint64_t c1, c2;

	c1 = get_cpu_cycles_64();

	node = root->rb_node;
	while (node != NULL) {
		const struct rb_node_super_ll *node_super_ll;
		int cmp_ret;

		node_super_ll = rb_entry_qual(node, struct rb_node_super_ll, rb, const);
		cmp_ret = cmp_func(k1, k2, node_super_ll);

		if (cmp_ret < 0) {
			node = node->rb_left;
		}
		else if (cmp_ret > 0) {
			node = node->rb_right;
		}
		else {
			node_super_ll_found = node_super_ll;
			break;
		}
	}
	c2 = get_cpu_cycles_64();

	if (tree_perf_ticks_enable) {
		c2 = c2 - c1;
		tree_perf_find_count++;
		tree_perf_find_ticks += c2;
	}

	return node_super_ll_found;
}

struct rb_node_super_ll *tree_perf_remove_at(struct rb_root *root, long k1, long k2,
		tree_perf_compar_f cmp_func)

{
	struct rb_node *node;
	struct rb_node_super_ll *node_super_ll_found = NULL;
	uint64_t c1, c2;

	c1 = get_cpu_cycles_64();

	node = root->rb_node;
	while (node != NULL) {
		struct rb_node_super_ll *node_super_ll;
		int cmp_ret;

		node_super_ll = rb_entry(node, struct rb_node_super_ll, rb);
		cmp_ret = cmp_func(k1, k2, node_super_ll);

		if (cmp_ret < 0) {
			node = node->rb_left;
		}
		else if (cmp_ret > 0) {
			node = node->rb_right;
		}
		else {
			node_super_ll_found = node_super_ll;
			break;
		}
	}
	if (node_super_ll_found) {
		rb_erase(&node_super_ll_found->rb, root);
	}
	c2 = get_cpu_cycles_64();

	if (tree_perf_ticks_enable) {
		c2 = c2 - c1;
		tree_perf_remove_count++;
		tree_perf_remove_ticks += c2;
	}


	return node_super_ll_found;
}

