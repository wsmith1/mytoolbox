#ifndef _MYTOOLBOX_TYPES_MYTOOLBOX_H
#define _MYTOOLBOX_TYPES_MYTOOLBOX_H

#ifndef __ASSEMBLY__

struct list_head {
	struct list_head *next, *prev;
};

struct hlist_node;

struct hlist_head {
	struct hlist_node *first;
};

struct hlist_node {
	struct hlist_node *next, **pprev;
};

#endif /*  __ASSEMBLY__ */
#endif /* _MYTOOLBOX_TYPES_MYTOOLBOX_H */

