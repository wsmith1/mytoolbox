#include <inttypes.h>
#include <malloc.h>
#include "mytoolbox/cpu_cycles.h"
#include "mytoolbox/rbtree.h"
#include "tree_callbacks2.h"

uint32_t tree_perf_count = 0;
uint64_t tree_perf_ticks = 0;

int tree_perf_insert(struct rb_root *root, long _new_key_k1, long _new_key_k2, struct rb_node *_new_node, tree_perf_compar_f compar_func)
{
	uint64_t c1, c2;
	struct rb_node **_new;
	struct rb_node *parent = NULL;

	c1 = get_cpu_cycles_64();
	_new = &root->rb_node;
	while ((*_new) != NULL) {
		int ret_cmp;

		parent = (*_new);

		ret_cmp = compar_func(_new_key_k1, _new_key_k2, parent);

		if (ret_cmp < 0) {
			_new = &parent->rb_left;
		}
		else if (ret_cmp > 0) {
			_new = &parent->rb_right;
		}
		else {
			return 0;
		}
	}

	rb_link_node(_new_node, parent, _new);
	rb_insert_color(_new_node, root);
	c2 = get_cpu_cycles_64();
	c2 = c2 - c1;
	tree_perf_count++;
	tree_perf_ticks += c2;
	return 1;

}

struct rb_node *tree_perf_find_at(const struct rb_root *root, long key1_k1, long key1_k2, tree_perf_compar_f compar_func)
{
	struct rb_node *node;
	const struct rb_node *node_found = NULL;

	uint64_t c1, c2;

	c1 = get_cpu_cycles_64();

	node = root->rb_node;
	while (node != NULL) {
		int ret_cmp;

		ret_cmp = compar_func(key1_k1, key1_k2, node);

		if (ret_cmp < 0) {
			node = node->rb_left;
		}
		else if (ret_cmp > 0) {
			node = node->rb_right;
		}
		else {
			node_found = node;
			break;
		}
	}
	c2 = get_cpu_cycles_64();

	c2 = c2 - c1;
	tree_perf_count++;
	tree_perf_ticks += c2;

	return (struct rb_node *)node_found;

}

struct rb_node *tree_perf_remove_at(struct rb_root *root, long key1_k1, long key1_k2, tree_perf_compar_f compar_func)
{
	struct rb_node *node;
	struct rb_node *node_found = NULL;

	uint64_t c1, c2;

	c1 = get_cpu_cycles_64();

	node = root->rb_node;
	while (node != NULL) {
		int ret_cmp;

		ret_cmp = compar_func(key1_k1, key1_k2, node);

		if (ret_cmp < 0) {
			node = node->rb_left;
		}
		else if (ret_cmp > 0) {
			node = node->rb_right;
		}
		else {
			node_found = node;
			break;
		}
	}

	if (node_found) {
		rb_erase(node_found, root);
	}
	c2 = get_cpu_cycles_64();

	c2 = c2 - c1;
	tree_perf_count++;
	tree_perf_ticks += c2;

	return node_found;

}





