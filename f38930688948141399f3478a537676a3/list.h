#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>
#include <stdint.h>

#define _LIST_HEAD(_)                   ((_node_t*)(_)->head)
#define _LIST_TAIL(_)                   ((_node_t*)(_)->tail)
#define _LIST_FRONT(_)                  ((void*)(_)->head->data)
#define _LIST_LAST(_)                   ((void*)(_)->tail->data)
#define _LIST_SIZE(_)                   ((size_t)(_)->size)
#define _NARGS(...)                     ((sizeof((size_t[]){0,##__VA_ARGS__})/sizeof(size_t))-1)
#define _LIST_PUSH_FRONT(_, ...)        (insert_list(_, 0, _NARGS(__VA_ARGS__), __VA_ARGS__))
#define _LIST_POP_FRONT(_)              (remove_list(_, 0))
#define _LIST_PUSH_BACK(_, ...)         (insert_list(_, _LIST_SIZE(_), \
                                            _NARGS(__VA_ARGS__), __VA_ARGS__))
#define _LIST_POP_BACK(_)               (remove_list(_, _LIST_SIZE(_) - 1))
#define _LIST_FOREACH_FRONT(_, _iter)   (_foreach_list(_, _iter, _FRONT))
#define _LIST_FOREACH_BACK(_, _iter)    (_foreach_list(_, _iter, _BACK))

#define _LIST_INIT_ITER(_, _iter, _dir) (_iter = NULL, _init_iter_list(_, _dir))
#define _LIST_NEXT_ITER(_, _iter)       (_iter = _next_iter_list(_))
#define _LIST_ITER_NODE(_)              ((_node_t*)((uint8_t*)(_) - offsetof(_node_t, data)))

typedef struct _node_t {
    struct _node_t* next;
    struct _node_t* prev;
    void*           data;
} _node_t;

typedef void      (*_dtor)(void*);
typedef void  (*_iterator)(void*);
typedef bool (*_predicate)(void*);

typedef enum {  _FRONT  = 0xDE,
                _BACK   = 0xAD } _direction;

typedef void** iter_t;
typedef struct {
    _node_t*    head;
    _node_t*    tail;
    size_t      size;
    _dtor       dtor;
    _node_t*    iter_node;
    _direction  curr : 0x08;
} list_t;

list_t*     make_list(_dtor)                                        __attribute__((nothrow));
void        free_list(list_t*)                                      __attribute__((nothrow));
bool        at_list(list_t const*, size_t, void**)                  __attribute__((nothrow));
list_t*     insert_list(list_t*, size_t, size_t, ...)               __attribute__((nothrow));
list_t*     remove_list(list_t*, size_t)                            __attribute__((nothrow));
list_t*     _foreach_list(list_t*, _iterator, _direction)           __attribute__((nothrow)); 
list_t*     _foreach_remove_list(list_t*, _predicate, _direction)   __attribute__((nothrow));
list_t*     reverse_list(list_t*)                                   __attribute__((nothrow));
void        _init_iter_list(list_t*, _direction)                    __attribute__((nothrow));
void**      _next_iter_list(list_t*)                                __attribute__((nothrow));

#endif /* _LIST_H */
