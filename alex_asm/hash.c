#include <stdlib.h>
#include <string.h>
#include "hash.h"

static hash_t*
_make_hash_size(size_t allc) {
    hash_t* hash = (hash_t*)malloc(sizeof(*hash));
    if (!hash)
        { return (_HASH_NULL); }
    (void)memset((void*)hash, 0, sizeof(*hash));
    hash->bucket = (_bucket_t)malloc(sizeof(*hash->bucket) * allc);
    if (!hash->bucket) {
        free((void*)hash);
        return (_HASH_NULL);
    }
    (void)memset(hash->bucket, 0, _HASH_DEFAULT);
    return (hash);
}

hash_t*
make_hash(_selector_t select, size_t climit, _destruct_t dtor, _duplicat_t dcpy) {
    if (!select)
        { return (_HASH_NULL); }
    hash_t* hash = _make_hash_size(_HASH_DEFAULT);
    if (!hash)
        { return (_HASH_NULL); }
    hash->climit    = climit;
    hash->select    = select;
    hash->allc      = _HASH_DEFAULT;
    hash->dtor      = dtor;
    hash->dcpy      = dcpy;
    return (hash);
}

void
free_hash(hash_t const* hash) {
    if (hash) {
        for (size_t i = 0; i < hash->allc; ++i)
            { free_list((list_t*)hash->bucket[i]); }
        free((void*)hash->bucket);
        free((void*)hash);
    }
}

hash_t*
copy_hash(hash_t const* hash) {
    if (!hash)
        { return (_HASH_NULL); }
    hash_t* new_hash = _make_hash_size(hash->allc);
    if (!new_hash)
        { return (_HASH_NULL); }
    size_t next_item = sizeof(_bucket_t);
    (void)memcpy(((uint8_t*)new_hash + next_item),
                 ((uint8_t*)hash + next_item), sizeof(*hash) - next_item);
    for (size_t i = 0; i < hash->allc; ++i) {
        new_hash->bucket[i] = _LIST_NULL;
        if (hash->bucket[i])
            { new_hash->bucket[i] = copy_list(hash->bucket[i]); }
    }
    return (new_hash);
}

static size_t
#if defined(__i386__) || defined(__x86_64__)
__attribute__((naked))
#endif /* defined(__i386__) || defined(__x86_64__) */
_round_up(
#if defined(__i386__) || defined(__x86_64__)
__attribute__((unused))
#endif /* defined(__i386__) || defined(__x86_64__) */
size_t _dummy) {
    #if defined(__i386__) || defined(__x86_64__)
        __asm__("xorl %edx, %edx");
        #if defined(__i386__)   // cdecl
            __asm__("bsrl dword ptr [%esp+0x04], %ecx");
        #else                   // system v
            __asm__("bsrq %rdi, %rcx");
        #endif /* defined(__i386__) */
        __asm__("cmovzl %edx, %ecx");
        __asm__("incb %cl");
        __asm__("xorl %eax, %eax");
        __asm__("incl %eax");
        __asm__("shll %cl, %eax");
        #if defined(__x86_64__)
            __asm__("movq $0x20, %rdi");
            __asm__("bzhiq %rdi, %rax, %rax");
            __asm__("retq");
        #else
            __asm__("retd");
        #endif /* defined(__i386__) */
    #else
        size_t placeholder = 0;
        for (int i = sizeof(size_t) - 1; i >= 0; --i) {
            if ((_dummy >> i) & 1) {
                placeholder = i + 1;
                break;
            }
        }
        return (1 << placeholder);
    #endif /* defined(__i386__) || defined(__x86_64__) */
}

static int
_expand_hash(hash_t* hash) {
    size_t new_size = _round_up(hash->allc);
    _bucket_t new_bucket = (_bucket_t)malloc(sizeof(*hash->bucket) * new_size);
    if (!new_bucket)
        { return (EXIT_FAILURE); }
    (void)memset((void*)new_bucket, 0, new_size);
    iter_hash_t iter;
    init_iter_hash(hash, &iter);
    element_t* element;
    while ((element = next_iter_hash(&iter))) {
        size_t _chash = _ELEMENT_GET_METADATA(element) % new_size;
        _node_t* parent = _ELEMENT_NODE(element);
        parent->prev = parent->next = _NODE_NULL;
        if (!new_bucket[_chash]) {
            new_bucket[_chash] = make_list(hash->dtor, hash->dcpy);
            new_bucket[_chash]->head = parent;
        }
        else {
            new_bucket[_chash]->tail->next = parent;
            parent->prev = new_bucket[_chash]->tail;
        }
        new_bucket[_chash]->tail = parent;
        ++new_bucket[_chash]->size;
    }
    for (size_t i = 0; i < hash->allc; ++i)
        { free((void*)hash->bucket[i]); }
    free((void*)hash->bucket);
    hash->size = new_size;
    hash->bucket = new_bucket;
    return (EXIT_SUCCESS);
}

hash_t*
insert_hash(hash_t* hash, size_t count, size_t apply, ...) {
    va_list start;
    va_start(start, apply);
    hash_t* _return = _insert_varg_hash(hash, count, apply, start);
    va_end(start);
    return (_return);
}

hash_t*
_insert_varg_hash(hash_t* hash, size_t count, size_t apply, va_list _start) {
    if (!hash || !count || (apply >= count))
        { return (_HASH_NULL); }
    va_list _copy;
    va_copy(_copy, _start);
    size_t _chash;
    for (size_t i = 0; i < count; ++i) {
        generic_t _data = va_arg(_copy, generic_t);
        if (apply == i)
            { _chash = ((*hash->select)(_data)); }
    }
    va_end(_copy);
    size_t new_index = _chash % hash->allc;
    _bucket_t const target = (hash->bucket + new_index);
    if (!(*target))
        { (*target) = make_list(hash->dtor, hash->dcpy); }
    else if (hash->climit)
        { ++hash->collid; }
    if (!_insert_varg_list(*target, _LIST_SIZE(*target), count, _start))
        { return (_HASH_NULL); }
    _ELEMENT_SET_METADATA(_LIST_LAST(*target), _chash);
    if ((hash->climit) && (hash->collid >= hash->climit)) {
        hash->climit <<= 1;
        hash->collid = 0;
        if (_expand_hash(hash) == EXIT_FAILURE)
            { return (_HASH_NULL); }
    }
    return (hash);

}

element_t
lookup_hash(hash_t const* hash, _elt_comp_t cmp, generic_t data) {
    if (!hash || !cmp)
        { return (_HASH_NULL); }
    size_t check_index = ((*hash->select)(data)) % hash->allc;
    if (!hash->bucket[check_index])
        { return (_GENERIC_NULL); }
    iter_list_t iter;
    init_iter_list(hash->bucket[check_index], &iter, FORWARD);
    element_t* element;
    while ((element = next_iter_list(&iter))) {
        if ((*cmp)(*element, data))
            { return (*element); }    
    }
    return (_GENERIC_NULL);
}

void
init_iter_hash(hash_t const* hash, iter_hash_t* iter) {
    if (!hash || !iter)
        { return; }
    iter->buck_base = _BUCKET_NULL;
    for (size_t i = 0; i < hash->allc; ++i) {
        if (hash->bucket[i]) {
            init_iter_list(hash->bucket[i], &iter->list_iter, FORWARD);
            iter->buck_base = hash->bucket + i;
            break;
        }
    }
    iter->buck_limt = (hash->bucket + hash->allc);
}

element_t*
next_iter_hash(iter_hash_t* iter) {
    if (!iter || !iter->buck_base)
        { return (_ELEMENT_NULL); }
    element_t* element;
    element = next_iter_list(&iter->list_iter);
    if (!element) {
        while ((++iter->buck_base) < iter->buck_limt) {
            if (*iter->buck_base) {
                init_iter_list(*iter->buck_base, &iter->list_iter, FORWARD);
                if ((element = next_iter_list(&iter->list_iter)))
                    { break; }
            }
        }
    }
    return (element);
}

size_t
hash_string(char const* string) {
    if (!string)
        { return (0); }
    size_t hash = 0;
    size_t mult = 1;
    for (size_t i = 0; string[i]; ++i) {
        hash += string[i] * mult;
        mult *= 0x100;
    }
    return (hash);
}

