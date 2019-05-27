#ifndef _BUFFER_H
#define _BUFFER_H

#include <stdlib.h>
#include <stdbool.h>

#define _BUFFER_NULL                (NULL)
#define _BUFFER_DEFAULT             (0x40)
#define _BUFFER_CACHE_DEFAULT       (0x10)
#define _BUFFER_STRING(_)           (_BUFFER_FLUSH(_), (char const*)(_)->string)
#define _BUFFER_GET_CURSOR(_)       (_BUFFER_FLUSH(_), (size_t)(_)->cursor)
#define _BUFFER_SET_CURSOR(_, _cur) (_BUFFER_FLUSH(_), \
                                        (_cur >= (_)->crsize) ? _cur : (_)->cursor = _cur)
#define _BUFFER_LIMIT(_)            (_BUFFER_FLUSH(_), (size_t)(_)->slimit)
#define _BUFFER_SIZE(_)             (_BUFFER_FLUSH(_), (size_t)(_)->crsize)
#define _BUFFER_REMOVE_CHAR(_)      (remove_size_buffer(_, 1))
#define _BUFFER_CACHE(_)            ((char const*)(_)->cache)
#define _BUFFER_FLUSH(_)            (_flush_cache_buffer(_))
#define _BUFFER_CACHE_FULL(_)       ((bool)((_)->icache >= _BUFFER_CACHE_DEFAULT))

typedef struct {
    char*   string;
    size_t  cursor;
    size_t  slimit;
    size_t  crsize;
    char*   lcache;
    size_t  icache;
} buffer_t;

buffer_t*       make_buffer(bool);
void            free_buffer(buffer_t const*);
buffer_t*       copy_buffer(buffer_t const*);
buffer_t*       insert_string_buffer(buffer_t*, char const*);
buffer_t*       insert_char_buffer(buffer_t*, char);
buffer_t*       remove_size_buffer(buffer_t*, size_t);
//char const*     last_word_buffer(buffer_t const*, )
buffer_t*       replace_buffer(buffer_t*, size_t, size_t, char const*);
void            _flush_cache_buffer(buffer_t*);

#endif /* _BUFFER_H */
