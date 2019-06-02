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

#ifndef _BUFFER_H
struct buffer_t;
typedef struct buffer_t buffer_t;
#endif /* _BUFFER_H */

#ifdef __GNUC__
__attribute__((nothrow))
#endif /* __GNUC__ */
buffer_t*   read_file(char const*);

#endif /* _UTILS_H */
