#include <stdlib.h>
#include "utils.h"

#if !defined(NDEBUG)
#include <stdio.h>
#include <assert.h>
void*
_xmalloc(size_t size, char const* function) {
    if (!size)
        { size = 1; }
    #undef malloc
    void* _chunk = malloc(size);
    #define     malloc(_)   (_xmalloc(_, __func__))
    if (!_chunk)
        { fprintf(stderr, "%s\n", function); }
    assert(_chunk);
    return (_chunk);
}
#endif /* !defined(NDEBUG) */

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

size_t
#if defined(_ASSEMBLY) && defined(__GNUC__)
__attribute__((naked))
#endif /* defined(_ASSEMBLY) && defined(__GNUC__) */
round_up(
#if defined(_ASSEMBLY) && defined(__GNUC__)
__attribute__((unused))
#endif /* defined(_ASSEMBLY) && defined(__GNUC__) */
size_t _dummy) {
    #ifdef _ASSEMBLY
        #if (!defined(__x86_64__)) && (!defined(__i386__))
            #error "UNABLE TO TARGET AN ARCHITECTURE"
        #endif /* !defined(__x86_64__) && !defined(__i386__) */
        __asm__("xorl       %edx, %edx");
        #if defined(__i386__)   // cdecl
            __asm__("bsrl   4(%esp), %ecx");
        #else                   // system v
            __asm__("bsrq   %rdi, %rcx");
        #endif /* defined(__i386__) */
        __asm__("cmovzl     %edx, %ecx");
        __asm__("incb       %cl");
        __asm__("xorl       %eax, %eax");
        __asm__("incl       %eax");
        __asm__("shll       %cl, %eax");
        #if defined(__x86_64__) // system v
            __asm__("movq   $0x20, %rdi");
            __asm__("bzhiq  %rdi, %rax, %rax");
            __asm__("retq");
        #else                   // cdecl
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
    #endif /* _ASSEMBLY */
}
