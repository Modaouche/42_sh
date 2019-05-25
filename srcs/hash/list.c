#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdarg.h>

#include "list.h"
#define _FREE_NODE(_node, _dtor)    if (_dtor) (*(_dtor))((_node)->data);\
                                    (_node)->next = (_node)->prev = NULL;\
                                    free((void*)(_node));

list_t*
make_list(_destruct_t dtor, _duplicat_t dcpy) {
    list_t* list = (list_t*)malloc(sizeof(*list));
    if (!list)
        { return (_LIST_NULL); }
    (void)memset(list, 0, sizeof(*list));
    list->dtor = dtor;
    list->dcpy = dcpy;
    return (list);
}

void
free_list(list_t* list) {
    if (list) {
        iter_list_t iter;
        init_iter_list(list, &iter, FORWARD);
        element_t element;
        while ((element = next_iter_list(&iter)))
            { _FREE_NODE(_ELEMENT_NODE(element), list->dtor); }
        free((void*)list);
    }
}

list_t*
copy_list(list_t const* list) {
    if (!list)
        { return (_LIST_NULL); }
    list_t* new_list = make_list(list->dtor, list->dcpy);
    if (!new_list)
        { return (_LIST_NULL); }
    iter_list_t iter;
    init_iter_list(list, &iter, FORWARD);
    element_t element;
    while ((element = next_iter_list(&iter))) {
        void* copy = *element;
        if (list->dcpy)
            { copy = (*list->dcpy)(*element); }
        _LIST_PUSH_BACK(new_list, copy);
    }
    return (new_list);
}


static _node_t*
_node_at_list(list_t const* list, size_t index) {
    if (!list)
        { return (_LIST_NULL); }
    else if (index >= list->size)
        { return (_LIST_NULL); }
    _node_t* iter = _LIST_NULL;
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

void**
at_list(list_t const* list, size_t index) {
    _node_t* node = _node_at_list(list, index);
    if (node)
        { return (&node->data); }
    return (_LIST_NULL);
}

list_t*
insert_list(list_t* list, size_t index, size_t count, ...) {
    if (!list)
        { return (_LIST_NULL); }
    if (!count)
        { return (list); }
    size_t size_node = sizeof(_node_t) + ((count - 1) * sizeof(void*));
    _node_t* new_node = (_node_t*)malloc(size_node);
    if (!new_node)
        { return (_LIST_NULL); }
    (void)memset((void*)new_node, 0, size_node);
    va_list _start;
    va_start(_start, count);
    size_t base_offset = offsetof(_node_t, data) / sizeof(void*);
    while (count--) {
        *(((void**)new_node) + base_offset) = va_arg(_start, void*);
        ++base_offset;
    }
    va_end(_start);
    if (!list->head || !list->tail) {
        if (list->head || list->tail)
            { return (_LIST_NULL); }
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
        { return (_LIST_NULL); }
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
_foreach_list(list_t* list, _iterator_t fiter, _direction direction) {
    if (!list || !list->head || !list->tail)
        { return (_LIST_NULL); }
    iter_list_t iter;
    init_iter_list(list, &iter, direction);
    element_t element;
    while ((element = next_iter_list(&iter)))
        { (*fiter)(*element); }
    return (list);
}

list_t*
_foreach_remove_list(list_t* list, _predicat_t pred, _direction direction) {
    if (!list || !pred)
        { return (_LIST_NULL); }
    iter_list_t iter;
    init_iter_list(list, &iter, direction);
    element_t element;
    while ((element = next_iter_list(&iter))) {
        if ((*pred)(*element)) {
            _node_t* parent = _ELEMENT_NODE(element);
            if (parent->prev)
                { parent->prev->next = parent->next; }
            else
                { list->head = parent->next; }
            if (parent->next)
                { parent->next->prev = parent->prev; }
            else
                { list->tail = _LIST_NULL; }
            _FREE_NODE(parent, list->dtor);
            --list->size;
        }
    }
    return (list);
}

list_t*
reverse_list(list_t* list) {
    if (!list)
        { return (_LIST_NULL); }
    iter_list_t iter;
    init_iter_list(list, &iter, FORWARD);
    _node_t* before = _LIST_NULL;
    element_t element;
    while ((element = next_iter_list(&iter))) {
        _node_t* current = _ELEMENT_NODE(element);
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
init_iter_list(list_t const* list, iter_list_t* iter, _direction direction) {
    if (!list || !iter)
        { return; }
    if ((direction == FORWARD) || (direction == REVERSE)) {
        iter->current = direction;
        iter->element = _ELEMENT_NULL;
        if (list->size) {
            if (direction == FORWARD)
                { iter->element = &list->head->data; }
            else if (direction == REVERSE)
                { iter->element = &list->tail->data; }
        }
    }
}

element_t
next_iter_list(iter_list_t* iter) {
    if (!iter || !iter->element)
        { return (_ELEMENT_NULL); }
    element_t data = iter->element;
    _node_t* target = NULL;
    if (iter->current == FORWARD)
        { target = _ELEMENT_NODE(data)->next; }
    else if (iter->current == REVERSE)
        { target = _ELEMENT_NODE(data)->prev; }
    iter->element = _ELEMENT_NULL;
    if (target)
        { iter->element = &target->data; }
    return (data);
}
