#ifndef _MYTOOLBOX_LIST_SORT_H
#define _MYTOOLBOX_LIST_SORT_H

struct list_head;

void list_sort(void *priv, struct list_head *head,
	       int (*cmp)(void *priv, const struct list_head *a,
			  const struct list_head *b));

int list_sort_test(void);

#endif /* _MYTOOLBOX_LIST_SORT_H */
