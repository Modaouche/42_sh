#ifndef _UTILS_H
#define _UTILS_H

#include <stdbool.h>
#include <stddef.h>

#define _NARGS(...)     ((sizeof((void*[]){0,##__VA_ARGS__}) / sizeof(void*)) - 1)
#define _READ_FILE(_)   (read_filde(open(_, O_RDONLY), true))

#if (!defined(NDEBUG))
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

struct buffer_t;
#ifdef __GNUC__
__attribute__((nothrow))
#endif /* __GNUC__ */
struct buffer_t*    read_filde(int, bool);

#endif /* _UTILS_H */
