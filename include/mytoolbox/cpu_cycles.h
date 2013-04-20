#ifndef __MYTOOLBOX_CPU_CYCLES_H
#define __MYTOOLBOX_CPU_CYCLES_H
#include <inttypes.h>
#include "mytoolbox/compiler.h"

#if (defined(__x86_64__))
#include "mytoolbox/cpu_cycles_x86_64.h"
#elif (defined(__i386__))
#include "mytoolbox/cpu_cycles_i386.h"
#elif (defined(__powerpc__))
#include "mytoolbox/cpu_cycles_powerpc.h"
#else
#error "'mytoolbox/cpu_cycles.h': Your architecture is not supported"
#endif

#endif /* __MYTOOLBOX_CPU_CYCLES_H */

