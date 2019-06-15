#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "buffer.h"

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
    #if defined(_ASSEMBLY) && defined(__GNUC__)
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
        for (int i = (sizeof(size_t) * 8) - 1; i >= 0; --i) {
            if ((_dummy >> i) & 1) {
                placeholder = i + 1;
                break;
            }
        }
        return (1 << placeholder);
    #endif /* defined(_ASSEMBLY) && defined(__GNUC__) */
}

#define _CHUNK_SIZE (1024)

buffer_t*
read_filde(int fd, bool _close) {
    if (fd == -1)
        { return (_BUFFER_NULL); }
    bool failure = false;
    buffer_t* buffer = make_buffer(true);
    if (!buffer)
        { failure = true; }
    char chunk[_CHUNK_SIZE + 1] = {};
    int rd;
    while ((!failure) && (rd = read(fd, chunk, _CHUNK_SIZE))) {
        if (rd != -1) {
            chunk[rd] = '\0';
            int size = 0;
            do {
                if (!insert_string_buffer(buffer, chunk + size)) { 
                    failure = true;
                    break;
                }
                size += strlen(chunk + size) + 1;
                if (rd >= size)
                    { _BUFFER_INSERT_CHAR(buffer, 0x00); }
            } while (rd > size);
        }
        else
            { failure = true; }
    }
    if (_close)
        { failure = close(fd); }
    if (failure) {
        free_buffer(buffer);
        return (_BUFFER_NULL);
    }
    return (buffer);
}
