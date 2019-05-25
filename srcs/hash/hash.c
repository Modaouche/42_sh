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
    (void)memset(hash->bucket, 0, _HASH_SIZE);
    return (hash);
}

hash_t*
make_hash(_selector_t select, size_t climit, _destruct_t dtor, _duplicat_t dcpy) {
    if (!select)
        { return (_HASH_NULL); }
    hash_t* hash = _make_hash_size(_HASH_SIZE);
    if (!hash)
        { return (_HASH_NULL); }
    hash->climit    = climit;
    hash->select    = select;
    hash->allc      = _HASH_SIZE;
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
    (void)memcpy(((uint8_t*)new_hash + offsetof(hash_t, bucket)),
                 ((uint8_t*)hash + offsetof(hash_t, bucket)), sizeof(*hash));
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
    size_t old_size = hash->allc;
    hash->allc = _round_up(hash->allc);
    _bucket_t old_bucket = hash->bucket;
    hash->bucket = (_bucket_t)malloc(sizeof(*hash->bucket) * hash->allc);
    int _exit = EXIT_SUCCESS;
    if (!hash->bucket)
        { _exit = EXIT_FAILURE; }
    else {
        (void)memset((void*)hash->bucket, 0, hash->allc);
        for (size_t i = 0; i < old_size; ++i) {
            if (old_bucket[i]) {
                if (!hash->bucket[i])
                    { hash->bucket[i] = make_list(hash->dtor, hash->dcpy); }
                iter_list_t iter;
                init_iter_list(old_bucket[i], &iter, FORWARD);
                element_t element;
                while ((element = next_iter_list(&iter))) {
                    _bucket_node_t* bnode = (_bucket_node_t*)_ELEMENT_NODE(element);
                    if (!bnode->need_recompute)
                        { _LIST_PUSH_BACK(hash->bucket[i], *element, (void*)false); }
                    else
                        { insert_hash(hash, *element); }
                }
            }
        }
    }
    for (size_t i = 0; i < old_size; ++i)
        { free_list(old_bucket[i]); }
    free((void*)old_bucket);
    return (_exit);
}

hash_t*
insert_hash(hash_t* hash, void* data) {
    if (!hash)
        { return (_HASH_NULL); }
    size_t new_index = ((*hash->select)(data));
    bool need_recompute = false;
    if (new_index >= hash->allc) {
        need_recompute = true;
        new_index %= hash->allc;
    }
    list_t** const target = (hash->bucket + new_index);
    if (!(*target))
        { (*target) = make_list(hash->dtor, hash->dcpy); }
    else if (hash->climit)
        { ++hash->collid; }
    (void)_LIST_PUSH_BACK(*target, data, (void*)need_recompute);
    if ((hash->climit) && (hash->collid >= hash->climit)) {
        hash->climit <<= 1;
        hash->collid = 0;
        if (_expand_hash(hash) == EXIT_FAILURE)
            { return (_HASH_NULL); }
    }
    return (hash);
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

element_t
next_iter_hash(iter_hash_t* iter) {
    if (!iter || !iter->buck_base)
        { return (_ELEMENT_NULL); }
    element_t element;
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

