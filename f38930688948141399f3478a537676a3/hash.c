#include <stdlib.h>
#include <string.h>
#include "hash.h"

hash_t*
make_hash(selector_t selector, size_t climit, _dtor dtor) {
    if (!selector)
        { return (NULL); }
    hash_t* hash = (hash_t*)malloc(sizeof(*hash));
    if (!hash)
        { return (NULL); }
    (void)memset((void*)hash, 0, sizeof(*hash));
    hash->bucket = (list_t**)malloc(sizeof(list_t*) * _HASH_SIZE);
    if (!hash->bucket) {
        free((void*)hash);
        return (NULL);
    }
    (void)memset(hash->bucket, 0, _HASH_SIZE);
    hash->size      = _HASH_SIZE;
    hash->climit    = climit;
    hash->selector  = selector;
    hash->dtor      = dtor;
    return (hash);
}

void
free_hash(hash_t const* hash) {
    if (hash) {
        for (size_t i = 0; i < hash->size; ++i)
            { free_list((list_t*)hash->bucket[i]); }
        free((void*)hash->bucket);
        free((void*)hash);
    }
}

static size_t
__attribute__((naked)) _round_up(size_t _dummy) {
    #if defined(__i386__) || defined(__x86_64__)
        __asm__("xord %edx, %edx");
        #if defined(__i386__) // cdecl
            __asm__("bsrd dword ptr [%esp+0x04], %ecx");
        #else // system v
            __asm__("bsrq %rdi, %ecx");
        #endif /* defined(__i386__) */
        __asm__("cmovzd %edx, %ecx");
        __asm__("incb %cl");
        __asm__("xord %eax, %eax");
        __asm__("incd %eax");
        __asm__("shld %cl, %eax");
        #if defined(__x86_64__)
            __asm__("movzxq %eax, %rax");
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
    size_t new_size = _round_up(hash->size);
    list_t** new_bucket = (list_t**)malloc(sizeof(list_t*) * new_size);
    if (!new_bucket)
        { return (EXIT_FAILURE); }
    (void)memset((void*)new_bucket, 0, new_size);
    for (size_t i = 0; i < hash->size; ++i)
        { new_bucket[i] = hash->bucket[i]; }
    free((void*)hash->bucket);
    hash->bucket = new_bucket;
    hash->size = new_size;
    hash->collid = 0;
    return (EXIT_SUCCESS);
}

hash_t*
insert_hash(hash_t* hash, void* data) {
    if (!hash)
        { return; }
    if ((hash->climit) && (hash->collid >= hash->climit)) {
        if (_expand_hash(hash) == EXIT_FAILURE)
            { return (NULL); }
    }
    size_t new_index = ((*hash->selector)(data));
    bool need_recompute = false;
    if (new_index >= hash->size) {
        need_recompute = true;
        new_index %= hash->size;
    }
    list_t** const target = (hash->bucket + new_index);
    if (!(*target))
        { (*target) = _LIST_NEW(_bucket_list_t, hash->dtor); }
    else if (hash->climit)
        { ++hash->collide; }
    (void)_LIST_PUSH_FRONT(*target, data);
    return (hash);
}

