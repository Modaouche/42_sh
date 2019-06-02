#include <string.h>

#include "buffer.h"
#include "utils.h"

buffer_t*
make_buffer(bool use_cache) {
    buffer_t* buffer = (buffer_t*)malloc(sizeof(*buffer));
    if (!buffer)
        { return (_BUFFER_NULL); }
    (void)memset((void*)buffer, 0, sizeof(*buffer));
    buffer->string = (char*)malloc(sizeof(char) * (_BUFFER_DEFAULT + 1));
    if (!buffer->string) {
        free((void*)buffer);
        return (_BUFFER_NULL);
    }
    (void)memset((void*)buffer->string, 0, sizeof(char) * (_BUFFER_DEFAULT + 1));
    buffer->slimit = _BUFFER_DEFAULT;
    if (use_cache) {
        buffer->lcache = (char*)malloc(sizeof(*buffer->lcache) * (_BUFFER_CACHE_DEFAULT + 1));
        if (!buffer->lcache) {
            free_buffer(buffer);
            return (_BUFFER_NULL);
        }
        (void)memset((void*)buffer->lcache, 0,
                sizeof(*buffer->lcache) * (_BUFFER_CACHE_DEFAULT + 1));
    }
    return (buffer);
}

void
free_buffer(buffer_t const* buffer) {
    if (buffer) {
        if (buffer->lcache)
            { free((void*)buffer->lcache); }
        free((void*)buffer->string);
        free((void*)buffer);
    }
}

buffer_t*
copy_buffer(buffer_t const* buffer) {
    if (!buffer)
        { return (_BUFFER_NULL); }
    buffer_t* new_buffer = (buffer_t*)malloc(sizeof(*new_buffer));
    if (!new_buffer)
        { return (_BUFFER_NULL); }
    (void)memcpy((void*)new_buffer, (void*)buffer, sizeof(*new_buffer));
    new_buffer->string = (char*)malloc(sizeof(char) * (buffer->slimit + 1));
    if (!new_buffer->string) {
        free((void*)new_buffer);
        return (_BUFFER_NULL);
    }
    (void)memcpy((void*)new_buffer->string, (void*)buffer->string,
                                        sizeof(char) * (buffer->slimit + 1));
    if (buffer->lcache) {
        new_buffer->lcache = (char*)malloc(sizeof(*new_buffer->lcache) *\
                                (_BUFFER_CACHE_DEFAULT + 1));
        if (!new_buffer->lcache) {
            free_buffer(new_buffer);
            return (_BUFFER_NULL);
        }
        (void)memcpy((void*)new_buffer->lcache, (void*)buffer->lcache,
                    sizeof(*new_buffer->lcache) * (_BUFFER_CACHE_DEFAULT + 1));
    }
    return (new_buffer);
}

static int
_expand_buffer(buffer_t* buffer, size_t unbound) {
    if (unbound < buffer->slimit)
        { return (0); }
    
    size_t new_size = round_up(unbound);
    char* new_string = (char*)malloc(sizeof(*new_string) * (new_size + 1));
    if (!new_string)
        { return (-1); } 
    (void)memcpy((void*)new_string, (void*)buffer->string,
                sizeof(*new_string) * buffer->slimit);
    (void)memset((void*)new_string + buffer->slimit, 0,
                sizeof(*new_string) * (new_size - buffer->slimit + 1));
    free((void*)buffer->string);
    buffer->string = new_string;
    buffer->slimit = new_size;
    return (0);
}

buffer_t*
insert_string_size_buffer(buffer_t* buffer, char const* string, size_t size) {
    if (!buffer || !string)
        { return (_BUFFER_NULL); }
    size_t len = strlen(string);
    if (size > len)
        { size = (len + 1); }
    if (!size)
        { return (buffer); }
    if (buffer->lcache) {
        do {
            _flush_cache_buffer(buffer);
            if (!size)
                { break; }
            buffer->icache += (size > _BUFFER_CACHE_DEFAULT) ? _BUFFER_CACHE_DEFAULT : size;
            if (size >= _BUFFER_CACHE_DEFAULT) {
                (void)memcpy((void*)buffer->lcache, (void*)string,
                                sizeof(char) * _BUFFER_CACHE_DEFAULT);
                string += _BUFFER_CACHE_DEFAULT;
                size   -= _BUFFER_CACHE_DEFAULT;
                continue;
            }
            (void)memcpy((void*)buffer->lcache, (void*)string, sizeof(char) * size);
            size ^= size;
        } while (_BUFFER_CACHE_FULL(buffer));
    } else {
        size_t target_len = (buffer->crsize + size);
        if ((target_len >= buffer->slimit) && (_expand_buffer(buffer, target_len)))
            { return (_BUFFER_NULL); }
        if (buffer->crsize) {
            (void)memmove((void*)(buffer->string + buffer->cursor + size),
                          (void*)(buffer->string + buffer->cursor),
                          sizeof(char) * (buffer->crsize - buffer->cursor));
        }
        (void)memcpy((void*)(buffer->string + buffer->cursor),
                     (void*)string, sizeof(char) * size);
        buffer->crsize += size;
        buffer->cursor += size;
        buffer->string[buffer->crsize] = '\0';
    }
    return (buffer);
}

buffer_t*
#if defined(_ASSEMBLY) && defined(__GNUC__)
__attribute__((naked))
#endif /* defined(_ASSEMBLY) && defined(__GNUC__) */
insert_string_buffer(
#if defined(_ASSEMBLY) && defined(__GNUC__)
__attribute__((unused))
#endif /* defined(_ASSEMBLY) && defined(__GNUC__) */
buffer_t* buffer,
#if defined(_ASSEMBLY) && defined(__GNUC__)
__attribute__((unused))
#endif /* defined(_ASSEMBLY) && defined(__GNUC__) */
char const* string) {
    #if defined(_ASSEMBLY) && defined(__GNUC__)
        #if defined(__x86_64__)     // system v
            __asm__("xorq   %rax, %rax");
            __asm__("testq  %rsi, %rsi");
//            __asm__("jz ");
            __asm__("xorq   %rcx, %rcx");
            __asm__("notq   %rcx");
            __asm__("xchgq  %rdi, %rsi");
            __asm__("repnz  scasb");
            __asm__("decq   %rcx");
            __asm__("notq   %rcx");
            __asm__("movq   %rcx, %rdx");
            __asm__("leaq   -%rcx(%rdi), %rdi");
            __asm__("xchgq  %rdi, %rsi");
            __asm__("callq  insert_string_size_buffer");
            __asm__("retq");
        #elif defined(__i386__)     // cdecl
        #else
            #error _BAD_ARCH
        #endif /* defined(__x86_64__) */
    #else
        if (!string)
            { return (_BUFFER_NULL); }
        return (insert_string_size_buffer(buffer, string, strlen(string)));
    #endif /* defined(_ASSEMBLY) && defined(__GNUC__) */
}

buffer_t*
remove_size_buffer(buffer_t* buffer, size_t size) {
    if (!buffer)
        { return (_BUFFER_NULL); }
    if ((buffer->lcache) && (buffer->icache)) {
        if (size > buffer->icache) {
            *(buffer->lcache) = '\0';
            size -= buffer->icache;
            buffer->icache ^= buffer->icache;
        } else {
            buffer->icache -= size;
            buffer->lcache[buffer->icache] = '\0';
            size ^= size;
        }
    }
    if (size > buffer->cursor)
        { size = buffer->cursor; }
    if (size) {
        (void)memmove(buffer->string + (buffer->cursor - size),
                                buffer->string + buffer->cursor,
                                sizeof(char) * (buffer->crsize - buffer->cursor));
        buffer->cursor -= size;
        buffer->crsize -= size;
        buffer->string[buffer->crsize] = '\0';
    }
    return (buffer);
}

buffer_t*
replace_buffer(buffer_t* buffer, size_t start, size_t size, char const* replace) {
    if (!buffer || !replace)
        { return (_BUFFER_NULL); }
    _flush_cache_buffer(buffer);
    if ((start >= buffer->crsize) || (!size))
        { return (buffer); }
    size_t len_replace = strlen(replace);
    size_t old_cursor = buffer->cursor;
    buffer->cursor = start + size;
    if ((start + size) > buffer->crsize) {
        size = (buffer->crsize - start);
        buffer->cursor = buffer->crsize;
    }
    if (len_replace > size) {
        (void)memcpy((void*)buffer->string + start, replace, sizeof(*replace) * size);
        insert_string_buffer(buffer, replace + size);
        _flush_cache_buffer(buffer);
    } else {
        (void)memcpy((void*)buffer->string + start, replace, sizeof(*replace) * len_replace);
        remove_size_buffer(buffer, size - len_replace);   
    }
    buffer->cursor = old_cursor;
    return (buffer);
}

void
_flush_cache_buffer(buffer_t* buffer) {
    if ((!buffer) || (!buffer->lcache))
        { return; }
    if (buffer->icache) {
        char* save_cache = buffer->lcache;
        buffer->lcache = NULL;
        insert_string_size_buffer(buffer, save_cache, buffer->icache);
        (void)memset((void*)save_cache, 0, sizeof(char) * (_BUFFER_CACHE_DEFAULT + 1));
        buffer->lcache = save_cache;
        buffer->icache ^= buffer->icache;
    }
}

buffer_t*
export_sub_buffer(buffer_t* buffer, size_t start, size_t limit) {
    _flush_cache_buffer(buffer);
    if ((!buffer) || (start >= buffer->slimit))
        { return (_BUFFER_NULL); }
    if ((start + limit) > buffer->slimit)
        { limit = (buffer->slimit - start); }
    buffer_t* sub_buffer = make_buffer((buffer->lcache) ? true : false);
    if (!sub_buffer)
        { return (_BUFFER_NULL); }
    else if (!insert_string_size_buffer(sub_buffer, buffer->string + start, limit)) {
        free_buffer(sub_buffer);
        return (_BUFFER_NULL);
    }
    return (sub_buffer);
}

