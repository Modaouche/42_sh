#ifndef _UTILS_H
#define _UTILS_H

#include <stddef.h>

#if !defined(NDEBUG)
#define     malloc(_)   (_xmalloc(_, __func__))
void*       _xmalloc(size_t, char const*);
#endif /* !defined(NDEBUG) */

#ifdef __GNUC__
__attribute__((nothrow))
#endif /* __GNUC__ */
size_t      hash_string(char const*);

#ifdef __GNUC__
__attribute__((nothrow))
#endif /* __GNUC__ */
size_t      round_up(size_t);

#endif /* _UTILS_H */
