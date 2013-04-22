#ifndef __MYTOOLBOX_COMPILER_H
#error "Please don't include 'mytoolbox/compiler-types-compat.h' directly, include 'mytoolbox/compiler.h' instead."
#endif /* __MYTOOLBOX_COMPILER_H */

/*
 * compile-time type checking.
 *
 * Author: Vladimir Olteanu <vladimir.olteanu@cs.pub.ro>
 *
 * Copyright (C) 2012 Vladimir Olteanu
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifdef __cplusplus

template <typename T, typename U> struct _types_compatible_p {
  static const bool result = false;
};

template <typename T> struct _types_compatible_p<T, T> {
  static const bool result = true;
};

#define __types_compatible_p(type1,type2) _types_compatible_p< type1, type2 >::result

#else /* __cplusplus */

#define __types_compatible_p(type1,type2) __builtin_types_compatible_p(type1,type2)

#endif /* __cplusplus */

