#ifndef _BUFFER_H
#define _BUFFER_H

#include <stdlib.h>
#include <stdbool.h>

#define _BUFFER_NULL                (NULL)
#define _BUFFER_DEFAULT             (0x40)
#define _BUFFER_CACHE_DEFAULT       (0x10)
#define _BUFFER_CURSOR_STRING(_)    (_BUFFER_FLUSH(_), (char const*)((_)->string + (_)->cursor))
#define _BUFFER_CURSOR_CHAR(_)      (_BUFFER_FLUSH(_), (char)(*_BUFFER_CURSOR_STRING(_)))
#define _BUFFER_STRING(_)           (_BUFFER_FLUSH(_), (char const*)(_)->string)
#define _BUFFER_GET_CURSOR(_)       (_BUFFER_FLUSH(_), (size_t)(_)->cursor)
#define _BUFFER_EOF(_)              (_BUFFER_FLUSH(_), ((_)->cursor >= (_)->crsize))
#define _BUFFER_SET_CURSOR(_, _cur) (_BUFFER_FLUSH(_), (size_t)\
                                        ((_cur > (_)->crsize) ?\
                                            ((_)->cursor = (_)->crsize) : ((_)->cursor = _cur)))

#define _BUFFER_FORWARD_CURSOR(_)   (_BUFFER_FLUSH(_), (size_t)\
                                        (((_)->cursor < (_)->crsize) ?\
                                                    (++(_)->cursor) : ((_)->cursor)))
#define _BUFFER_REVERSE_CURSOR(_)   (_BUFFER_FLUSH(_), (size_t)\
                                        (((_)->cursor) ? (--(_)->cursor) : ((_)->cursor)))

#define _BUFFER_LIMIT(_)            (_BUFFER_FLUSH(_), (size_t)(_)->slimit)
#define _BUFFER_SIZE(_)             (_BUFFER_FLUSH(_), (size_t)(_)->crsize)
#define _BUFFER_INSERT_CHAR(_, _ch) (insert_string_size_buffer(_,\
                                        (char const*)&(char[]){_ch, 0x00}, 0x01))

#define _BUFFER_APPEND(_, _bf)      (insert_string_buffer(_, _BUFFER_STRING(_bf)))
#define _BUFFER_REMOVE_CHAR(_)      (remove_size_buffer(_, 0x01))
#define _BUFFER_CACHE(_)            ((char const*)(_)->cache)
#define _BUFFER_FLUSH(_)            (_flush_cache_buffer(_))
#define _BUFFER_CACHE_FULL(_)       ((bool)((_)->icache >= _BUFFER_CACHE_DEFAULT))

typedef size_t (*_match_t)(char const*, size_t);

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
buffer_t*       insert_string_size_buffer(buffer_t*, char const*, size_t);
buffer_t*       insert_string_buffer(buffer_t*, char const*);
buffer_t*       remove_size_buffer(buffer_t*, size_t);
buffer_t*       replace_buffer(buffer_t*, size_t, size_t, char const*);
void            _flush_cache_buffer(buffer_t*);
buffer_t*       export_sub_buffer(buffer_t*, size_t, size_t);
buffer_t*       remove_match_buffer(buffer_t*, _match_t, size_t*);

#endif /* _BUFFER_H */
