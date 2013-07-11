#include <inttypes.h>
#include <malloc.h>
#include "mytoolbox/cpu_cycles.h"
#include "mytoolbox/rbtree.h"
#include "tree_embedded.h"

uint32_t tree_perf_count = 0;
uint64_t tree_perf_ticks = 0;

int tree_perf_insert(struct rb_root *root, struct my_tree_node_ll_s *my_node)
{
	uint64_t c1, c2;
	struct rb_node **_new;
	struct rb_node *parent = NULL;

	c1 = get_cpu_cycles_64();
	_new = &root->rb_node;
	while ((*_new) != NULL) {
		const struct my_tree_node_ll_s *parent_node_ll;

		parent = (*_new);
		parent_node_ll = rb_entry_qual(parent, struct my_tree_node_ll_s, rb, const);

		if (my_node->k1 < parent_node_ll->k1) {
			_new = &parent->rb_left;
		}
		else if (my_node->k1 > parent_node_ll->k1) {
			_new = &parent->rb_right;
		}
		else {
			if (my_node->k2 < parent_node_ll->k2) {
				_new = &parent->rb_left;
			}
			else if (my_node->k2 > parent_node_ll->k2) {
				_new = &parent->rb_right;
			}
			else {
				return 0;
			}
		}
	}

	rb_link_node(&my_node->rb, parent, _new);
	rb_insert_color(&my_node->rb, root);
	c2 = get_cpu_cycles_64();
	c2 = c2 - c1;
	tree_perf_count++;
	tree_perf_ticks += c2;
	return 1;

}

struct my_tree_node_ll_s *tree_perf_find_at(const struct rb_root *root, long k1, long k2)
{
	struct rb_node *node;
	const struct my_tree_node_ll_s *node_ll_found = NULL;

	uint64_t c1, c2;

	c1 = get_cpu_cycles_64();

	node = root->rb_node;
	while (node != NULL) {
		const struct my_tree_node_ll_s *node_ll;

		node_ll = rb_entry_qual(node, struct my_tree_node_ll_s, rb, const);

		if (k1 < node_ll->k1) {
			node = node->rb_left;
		}
		else if (k1 > node_ll->k1) {
			node = node->rb_right;
		}
		else {
			if (k2 < node_ll->k2) {
				node = node->rb_left;
			}
			else if (k2 > node_ll->k2) {
				node = node->rb_right;
			}
			else {
				node_ll_found = node_ll;
				break;
			}
		}
	}
	c2 = get_cpu_cycles_64();

	c2 = c2 - c1;
	tree_perf_count++;
	tree_perf_ticks += c2;

	return (struct my_tree_node_ll_s *)node_ll_found;

}

struct my_tree_node_ll_s *tree_perf_remove_at(struct rb_root *root, long k1, long k2)
{
	struct rb_node *node;
	struct my_tree_node_ll_s *node_ll_found = NULL;

	uint64_t c1, c2;

	c1 = get_cpu_cycles_64();

	node = root->rb_node;
	while (node != NULL) {
		struct my_tree_node_ll_s *node_ll;

		node_ll = rb_entry(node, struct my_tree_node_ll_s, rb);

		if (k1 < node_ll->k1) {
			node = node->rb_left;
		}
		else if (k1 > node_ll->k1) {
			node = node->rb_right;
		}
		else {
			if (k2 < node_ll->k2) {
				node = node->rb_left;
			}
			else if (k2 > node_ll->k2) {
				node = node->rb_right;
			}
			else {
				node_ll_found = node_ll;
				break;
			}
		}
	}
	if (node_ll_found) {
		rb_erase(&node_ll_found->rb, root);
	}
	c2 = get_cpu_cycles_64();

	c2 = c2 - c1;
	tree_perf_count++;
	tree_perf_ticks += c2;

	return node_ll_found;

}


