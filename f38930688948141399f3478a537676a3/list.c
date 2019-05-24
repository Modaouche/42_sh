#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdarg.h>

#include "list.h"
#define _FREE_NODE(_node, _dtor)    if (_dtor) (*(_dtor))((_node)->data);\
                                    free((void*)(_node));

list_t*
make_list(_dtor dtor) {
    list_t* list = (list_t*)malloc(sizeof(*list));
    if (!list)
        { return (NULL); }
    (void)memset(list, 0, sizeof(*list));
    list->dtor = dtor;
    list->curr = _FRONT;
    return (list);
}

void
free_list(list_t* list) {
    if (list) {
        void** iter;
        _LIST_INIT_ITER(list, iter, _FRONT);
        while (_LIST_NEXT_ITER(list, iter))
            { _FREE_NODE(_LIST_ITER_NODE(iter), list->dtor); }
        free((void*)list);
    }
}

static _node_t*
_node_at_list(list_t const* list, size_t index) {
    if (!list)
        { return (NULL); }
    else if (index >= list->size)
        { return (NULL); }
    _node_t* iter = NULL;
    if (index < (list->size >> 1)) {
        iter = list->head;
        while (index--)
            { iter = iter->next; }
    } else {
        iter = list->tail;
        while (++index < list->size)
            { iter = iter->prev; }
    }
    return (iter);
}

bool
at_list(list_t const* list, size_t index, void** _data) {
    if (!_data)
        { return (false); }
    _node_t* node = _node_at_list(list, index);
    if (node)
        { (*_data) = node->data; }
    return ((bool)node);
}

list_t*
insert_list(list_t* list, size_t index, size_t count, ...) {
    if (!list)
        { return (NULL); }
    if (!count)
        { return (list); }
    size_t size_node = sizeof(_node_t) + ((count - 1) * sizeof(void*));
    _node_t* new_node = (_node_t*)malloc(size_node);
    if (!new_node)
        { return (NULL); }
    (void)memset((void*)new_node, 0, size_node);
    va_list _start;
    va_start(_start, count);
    size_t base_offset = offsetof(_node_t, data) / sizeof(void*);
    while (count--) {
        *(((void**)new_node) + base_offset) = va_arg(_start, void*);
        ++base_offset;
    }
    va_end(_start);
    if (!list->head) {
        list->head = new_node;
        list->tail = new_node;    
    } else {
        _node_t* target = _node_at_list(list, index);
        if (!target) {
            list->tail->next = new_node;
            new_node->prev = list->tail;
            list->tail = new_node;
        } else {
            if (target->prev)
                { target->prev->next = new_node; }
            else
                { list->head = new_node; }

            if (target->next)
                { target->next->prev = new_node; }
            new_node->next = target;
            new_node->prev = target->prev;
            target->prev = new_node;
        }
    }
    ++list->size;
    return (list);
}

list_t*
remove_list(list_t* list, size_t index) {
    if (!list)
        { return (NULL); }
    if (!list->size)
        { return (list); }
    _node_t* target = _node_at_list(list, index);
    if (!target)
        { target = list->tail; }

    if (target->prev)
        { target->prev->next = target->next; }
    else
        { list->head = target->next; }
    if (target->next)
        { target->next->prev = target->prev; }
    else
        { list->tail = target->prev; }
    _FREE_NODE(target, list->dtor);
    --list->size;
    return (list);
}

list_t*
_foreach_list(list_t* list, _iterator fiter, _direction dir) {
    if (!list || !list->head)
        { return (NULL); }
    void** iter;
    _LIST_INIT_ITER(list, iter, dir);
    while (_LIST_NEXT_ITER(list, iter))
        { (*fiter)(*iter); }
    return (list);
}

list_t*
_foreach_remove_list(list_t* list, _predicate pred, _direction dir) {
    if (!list || !pred)
        { return (NULL); }
    void** iter;
    _LIST_INIT_ITER(list, iter, dir);
    while (_LIST_NEXT_ITER(list, iter)) {
        _node_t* parent = _LIST_ITER_NODE(iter);
        if ((*pred)(*iter)) {
            if (parent->prev)
                { parent->prev->next = parent->next; }
            else
                { list->head = parent->next; }
            if (parent->next)
                { parent->next->prev = parent->prev; }
            else
                { list->tail = NULL; }
            _FREE_NODE(parent, list->dtor);
        }
    }
    return (list);
}

list_t*
reverse_list(list_t* list) {
    if (!list)
        { return (NULL); }
    iter_t iter;
    _LIST_INIT_ITER(list, iter, _FRONT);
    _node_t* before = NULL;
    while (_LIST_NEXT_ITER(list, iter)) {
        _node_t* current = _LIST_ITER_NODE(iter);
        current->prev = current->next;
        current->next = before;
        before = current;
    }
    list->head = (_node_t*)((size_t)list->head ^ (size_t)list->tail);
    list->tail = (_node_t*)((size_t)list->tail ^ (size_t)list->head);
    list->head = (_node_t*)((size_t)list->head ^ (size_t)list->tail);
    return (list);
}

void
_init_iter_list(list_t* list, _direction dir) {
    if (!list)
        { return; }
    list->curr = dir;
    list->iter_node = NULL;
    if (dir == _FRONT)
        { list->iter_node = list->head; }
    else if (dir == _BACK)
        { list->iter_node = list->tail; }
}

void**
_next_iter_list(list_t* list) {
    if (!list || !list->iter_node)
        { return (NULL); }
    void** data = &list->iter_node->data;
    if (list->curr == _FRONT)
        { list->iter_node = list->iter_node->next; }
    else if (list->curr == _BACK)
        { list->iter_node = list->iter_node->prev; }
    return (data);
}
