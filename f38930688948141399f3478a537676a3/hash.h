#ifndef _HASH_H
#define _HASH_H

#include <stddef.h>
#include "list.h"

#define _HASH_SIZE                  (0x50)
#define _HASH_GET_SIZE(_)           ((size_t)(_)->size)
#define _HASH_GET_COUNT(_)          ((size_t)(_)->count)
#define _HASH_SET_SELECTOR(_, v)    ((selector_t)(_)->selector = v)

typedef struct {
    list_t  body;
    bool    need_recompute;
} _bucket_list_t;

typedef size_t (*selector_t)(void*);
typedef struct {
    _bucket_list_t**    bucket;
    size_t              size, count;
    size_t              collid;
    size_t              climit;
    selector_t          selector;
    _dtor               dtor;
    list_t*             iter;
} hash_t;

hash_t*     make_hash(selector_t, size_t, _dtor)    __attribute__((nothrow));
void        free_hash(hash_t const*)                __attribute__((nothrow));
hash_t*     insert_hash(hash_t*, void*)             __attribute__((nothrow));
void    remove_hash(hash_t*, void*);
bool    lookup_hash(hash_t const*, void*);


#endif /* _HASH_H */
