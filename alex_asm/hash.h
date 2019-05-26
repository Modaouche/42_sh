#ifndef _HASH_H
#define _HASH_H

#include <stddef.h>
#include "list.h"

#define _HASH_NULL                  (NULL)
#define _BUCKET_NULL                (NULL)
#define _HASH_DEFAULT               (0x100)
#define _HASH_SIZE(_)               ((size_t)(_)->size)
#define _HASH_SELECTOR(_)           ((selector_t)(_)->selector)

typedef list_t**    _bucket_t;
typedef size_t      (*_selector_t)(generic_t);
typedef bool        (*_elt_comp_t)(element_t, generic_t);

typedef struct {
    iter_list_t list_iter;
    _bucket_t   buck_base;
    _bucket_t   buck_limt;
} iter_hash_t;

typedef struct {
    _bucket_t           bucket;
    size_t              collid;
    size_t              climit;
    _selector_t         select;
    size_t              allc;
    size_t              size;
    _destruct_t         dtor;
    _duplicat_t         dcpy;
} hash_t;

hash_t*     make_hash(_selector_t, size_t, _destruct_t, _duplicat_t) __attribute__((nothrow));
void        free_hash(hash_t const*)                                 __attribute__((nothrow));
hash_t*     copy_hash(hash_t const*)                                 __attribute__((nothrow));
hash_t*     insert_hash(hash_t*, size_t, size_t, ...)                __attribute__((nothrow));
hash_t*     _insert_varg_hash(hash_t*, size_t, size_t, va_list)      __attribute__((nothrow));
void        remove_hash(hash_t*, void*)                              __attribute__((nothrow));
element_t   lookup_hash(hash_t const*, _elt_comp_t, generic_t)       __attribute__((nothrow));
void        init_iter_hash(hash_t const*, iter_hash_t*)              __attribute__((nothrow));
element_t*  next_iter_hash(iter_hash_t*)                             __attribute__((nothrow));
size_t      hash_string(char const*)                                 __attribute__((nothrow));

#endif /* _HASH_H */
