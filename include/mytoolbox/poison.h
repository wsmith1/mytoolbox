#ifndef _MYTOOLBOX_POISON_H
#define _MYTOOLBOX_POISON_H

/********** include/linux/list.h **********/

/*
 * Architectures might want to move the poison pointer offset
 * into some well-recognized area such as 0xdead000000000000,
 * that is also not mappable by user-space exploits:
 */
#define POISON_POINTER_DELTA 0

/*
 * These are non-NULL pointers that will result in page faults
 * under normal circumstances, used to verify that nobody uses
 * non-initialized list entries.
 */
#define LIST_POISON1  ((void *) ((unsigned char *) 0x00100100 + POISON_POINTER_DELTA))
#define LIST_POISON2  ((void *) ((unsigned char *) 0x00200200 + POISON_POINTER_DELTA))

#endif /* _MYTOOLBOX_POISON_H */
