#ifndef _MYTOOLBOX_BUG_WARN_H
#define _MYTOOLBOX_BUG_WARN_H
#include <stdio.h>
#include "mytoolbox/compiler.h"

#define __WARN_printf(arg...)	do { fprintf(stderr, arg); } while (0)

#define WARN(condition, format...) ({		\
	int __ret_warn_on = !!(condition);	\
	if (unlikely(__ret_warn_on))		\
		__WARN_printf(format);		\
	unlikely(__ret_warn_on);		\
})

#define WARN_ON(condition) ({						\
	int __ret_warn_on = !!(condition);				\
	if (unlikely(__ret_warn_on))					\
		__WARN_printf("WARNING: '%s'\n", #condition);						\
	unlikely(__ret_warn_on);					\
})

#define WARN_ON_ONCE(condition)	({	\
	static int __warned;			\
	int __ret_warn_once = !!(condition);	\
						\
	if (unlikely(__ret_warn_once))		\
		if (WARN(!__warned, "WARNING: '%s'\n", #condition)) 	\
			__warned = 1;		\
	unlikely(__ret_warn_once);		\
})

#define WARN_ONCE(condition, format...)	({	\
	static int __warned;			\
	int __ret_warn_once = !!(condition);	\
						\
	if (unlikely(__ret_warn_once))		\
		if (WARN(!__warned, format)) 	\
			__warned = 1;		\
	unlikely(__ret_warn_once);		\
})
#endif /* _MYTOOLBOX_BUG_WARN_H */

