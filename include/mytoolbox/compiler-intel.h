#ifndef __MYTOOLBOX_COMPILER_H
#error "Please don't include 'mytoolbox/compiler-intel.h' directly, include 'mytoolbox/compiler.h' instead."
#endif /* __MYTOOLBOX_COMPILER_H */

#ifdef __ECC

/* Some compiler specific definitions are overwritten here
 * for Intel ECC compiler
 */

/* Intel ECC compiler doesn't support gcc specific asm stmts.
 * It uses intrinsics to do the equivalent things.
 */
#undef barrier
#undef RELOC_HIDE

#define barrier() __memory_barrier()

#define RELOC_HIDE(ptr, off)					\
  ({ unsigned long __ptr;					\
     __ptr = (unsigned long) (ptr);				\
    (typeof(ptr)) (__ptr + (off)); })

/* Intel ECC compiler doesn't support __builtin_types_compatible_p() */
#define __must_be_array(a) 0

#endif /* __ECC */

#define uninitialized_var(x) x

