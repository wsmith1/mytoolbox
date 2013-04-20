#ifndef _MYTOOLBOX_STDDEF_MYTOOLBOX_H
#define _MYTOOLBOX_STDDEF_MYTOOLBOX_H

/* For offsetof() macro definition */
#include <stddef.h>
/* For __compiler_offsetof() macro definition */
#include "mytoolbox/compiler.h"

enum {
	false	= 0,
	true	= 1
};

#ifndef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE,MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else /* !__compiler_offsetof */
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif /* !__compiler_offsetof */
#endif /* offsetof */

#endif /* _MYTOOLBOX_STDDEF_MYTOOLBOX_H */
