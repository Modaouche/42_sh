#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>
#include <stdint.h>

#define _NARGS(...)                     ((sizeof((void*[]){0,##__VA_ARGS__})/sizeof(void*))-1)

#define _LIST_NULL                      (NULL)
#define _LIST_HEAD(_)                   ((_node_t*)(_)->head)
#define _LIST_TAIL(_)                   ((_node_t*)(_)->tail)
#define _LIST_FRONT(_)                  ((void*)(_)->head->data)
#define _LIST_LAST(_)                   ((void*)(_)->tail->data)
#define _LIST_SIZE(_)                   ((size_t)(_)->size)
#define _LIST_PUSH_FRONT(_, ...)        (insert_list(_, 0, _NARGS(__VA_ARGS__), __VA_ARGS__))
#define _LIST_POP_FRONT(_)              (remove_list(_, 0))
#define _LIST_PUSH_BACK(_, ...)         (insert_list(_, _LIST_SIZE(_), \
                                            _NARGS(__VA_ARGS__), __VA_ARGS__))
#define _LIST_POP_BACK(_)               (remove_list(_, _LIST_SIZE(_) - 1))
#define _LIST_FOREACH_FRONT(_, _iter)   (_foreach_list(_, _iter, FORWARD))
#define _LIST_FOREACH_BACK(_, _iter)    (_foreach_list(_, _iter, REVERSE))
#define _LIST_REMOVE_FRONT(_, _iter)    (_foreach_remove_list(_, _iter, FORWARD))
#define _LIST_REMOVE_BACK(_, _iter)     (_foreach_remove_list(_, _iter, REVERSE))

#define _ELEMENT_NULL                   (NULL)
#define _ELEMENT_NODE(_)                ((_node_t*)((uint8_t*)(_) - offsetof(_node_t, data)))

typedef struct _node_t {
    struct _node_t* next;
    struct _node_t* prev;
    void*           data;
} _node_t;

typedef void    (*_destruct_t)(void*);
typedef void*   (*_duplicat_t)(void*);
typedef void    (*_iterator_t)(void*);
typedef bool    (*_predicat_t)(void*);

typedef enum {  FORWARD = 0xDE,
                REVERSE = 0xAD } _direction;

typedef void** element_t;
typedef struct {
    element_t   element;
    _direction  current : 0x08;
} iter_list_t;

typedef struct {
    _node_t*    head;
    _node_t*    tail;
    size_t      size;
    _destruct_t dtor;
    _duplicat_t dcpy;
} list_t;

list_t*     make_list(_destruct_t, _duplicat_t)                     __attribute__((nothrow));
void        free_list(list_t*)                                      __attribute__((nothrow));
list_t*     copy_list(list_t const*)                                __attribute__((nothrow));
void**      at_list(list_t const*, size_t)                          __attribute__((nothrow));
list_t*     insert_list(list_t*, size_t, size_t, ...)               __attribute__((nothrow));
list_t*     remove_list(list_t*, size_t)                            __attribute__((nothrow));
list_t*     _foreach_list(list_t*, _iterator_t, _direction)         __attribute__((nothrow)); 
list_t*     _foreach_remove_list(list_t*, _predicat_t, _direction)  __attribute__((nothrow));
list_t*     reverse_list(list_t*)                                   __attribute__((nothrow));
void        init_iter_list(list_t const*, iter_list_t*, _direction) __attribute__((nothrow));
element_t   next_iter_list(iter_list_t*)                            __attribute__((nothrow));

#endif /* _LIST_H */
