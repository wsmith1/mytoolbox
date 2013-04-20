#ifndef __MYTOOLBOX_COMPILER_H
#error "Please don't include 'mytoolbox/compiler-gcc3.h' directly, include 'mytoolbox/compiler.h' instead."
#endif /* __MYTOOLBOX_COMPILER_H */

#if __GNUC_MINOR__ < 2
# error Sorry, your compiler is too old - please upgrade it.
#endif

#if __GNUC_MINOR__ >= 3
# define __used			__attribute__((__used__))
#else
# define __used			__attribute__((__unused__))
#endif

#if __GNUC_MINOR__ >= 4
#define __must_check		__attribute__((warn_unused_result))
#endif

