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

struct tree_perf_entry_s {
	void *data;
	struct rb_node rb;
};

int tree_perf_insert(struct rb_root *root, long new_k1, long new_k2, void *new_data,
		tree_perf_compar_f cmp_func)
{
	struct tree_perf_entry_s *ent;
	uint64_t c1, c2;
	struct rb_node **_new;
	struct rb_node *parent = NULL;

	ent = calloc(1, sizeof(*ent));
	if (!ent) {
		return 0;
	}
	ent->data = new_data;

	c1 = get_cpu_cycles_64();
	_new = &root->rb_node;
	while ((*_new) != NULL) {
		const struct tree_perf_entry_s *parent_entry;
		const void *parent_data;
		int cmp_ret;

		parent = (*_new);
		parent_entry = rb_entry_qual(parent, struct tree_perf_entry_s, rb, const);
		parent_data = parent_entry->data;

		cmp_ret = cmp_func(new_k1, new_k2, parent_data);
		if (cmp_ret < 0) {
			_new = &parent->rb_left;
		}
		else if (cmp_ret > 0) {
			_new = &parent->rb_right;
		}
		else {
			free(ent);
			return 0;
		}
	}

	rb_link_node(&ent->rb, parent, _new);
	rb_insert_color(&ent->rb, root);
	c2 = get_cpu_cycles_64();
	if (tree_perf_ticks_enable) {
		c2 = c2 - c1;
		tree_perf_insert_count++;
		tree_perf_insert_ticks += c2;
	}
	return 1;
}

const void *tree_perf_find_at(struct rb_root *root, long k1, long k2,
		tree_perf_compar_f cmp_func)
{
	struct rb_node *node;
	const void *data_found = NULL;
	uint64_t c1, c2;

	c1 = get_cpu_cycles_64();

	node = root->rb_node;
	while (node != NULL) {
		const struct tree_perf_entry_s *ent;
		const void *data;
		int cmp_ret;

		ent = rb_entry_qual(node, struct tree_perf_entry_s, rb, const);
		data = ent->data;
		cmp_ret = cmp_func(k1, k2, data);

		if (cmp_ret < 0) {
			node = node->rb_left;
		}
		else if (cmp_ret > 0) {
			node = node->rb_right;
		}
		else {
			data_found = data;
			break;
		}
	}
	c2 = get_cpu_cycles_64();

	if (tree_perf_ticks_enable) {
		c2 = c2 - c1;
		tree_perf_find_count++;
		tree_perf_find_ticks += c2;
	}

	return data_found;
}

void *tree_perf_remove_at(struct rb_root *root, long k1, long k2,
		tree_perf_compar_f cmp_func)

{
	struct rb_node *node;
	struct tree_perf_entry_s *ent_found = NULL;
	void *data_found = NULL;
	uint64_t c1, c2;

	c1 = get_cpu_cycles_64();

	node = root->rb_node;
	while (node != NULL) {
		struct tree_perf_entry_s *ent;
		void *data;
		int cmp_ret;

		ent = rb_entry(node, struct tree_perf_entry_s, rb);
		data = ent->data;
		cmp_ret = cmp_func(k1, k2, data);

		if (cmp_ret < 0) {
			node = node->rb_left;
		}
		else if (cmp_ret > 0) {
			node = node->rb_right;
		}
		else {
			ent_found = ent;
			data_found = data;
			break;
		}
	}
	if (ent_found) {
		rb_erase(&ent_found->rb, root);
	}
	c2 = get_cpu_cycles_64();

	if (tree_perf_ticks_enable) {
		c2 = c2 - c1;
		tree_perf_remove_count++;
		tree_perf_remove_ticks += c2;
	}

	free(ent_found);

	return data_found;
}

