#include <string.h>

#include "buffer.h"
#include "utils.h"

buffer_t*
make_buffer(bool use_cache) {
    buffer_t* buffer = (buffer_t*)malloc(sizeof(*buffer));
    if (!buffer)
        { return (_BUFFER_NULL); }
    (void)memset((void*)buffer, 0, sizeof(*buffer));
    buffer->string = (char*)malloc(sizeof(char) * _BUFFER_DEFAULT);
    if (!buffer->string) {
        free((void*)buffer);
        return (_BUFFER_NULL);
    }
    (void)memset((void*)buffer->string, 0, sizeof(char) * _BUFFER_DEFAULT);
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
    new_buffer->string = (char*)malloc(sizeof(char) * buffer->slimit);
    if (!new_buffer->string) {
        free((void*)new_buffer);
        return (_BUFFER_NULL);
    }
    (void)strcpy(new_buffer->string, buffer->string);
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

buffer_t*
insert_string_buffer(buffer_t* buffer, char const* string) {
    if (!buffer || !string)
        { return (_BUFFER_NULL); }
    size_t len = strlen(string);
    if (!len)
        { return (buffer); }
    if (buffer->lcache) {
        while (_BUFFER_CACHE_FULL(buffer)) {
            _flush_cache_buffer(buffer);
            if (!len)
                { break; }
            buffer->icache += len;
            if (len >= _BUFFER_CACHE_DEFAULT) {
                (void)memcpy((void*)buffer->lcache, (void*)string,
                                sizeof(char) * _BUFFER_CACHE_DEFAULT);
                string += _BUFFER_CACHE_DEFAULT;
                len    -= _BUFFER_CACHE_DEFAULT;
                continue;
            }
            (void)memcpy((void*)buffer->lcache, (void*)string, sizeof(char) * len);
            len ^= len;
        }
    } else {
        if ((buffer->crsize + len) >= buffer->slimit) { /* TODO */ }
        if (buffer->crsize) {
            (void)memmove((void*)(buffer->string + buffer->cursor + len),
                          (void*)(buffer->string + buffer->cursor),
                          sizeof(char) * (buffer->crsize - buffer->cursor));
        }
        (void)memcpy((void*)(buffer->string + buffer->cursor),
                     (void*)string, sizeof(char) * len);
        buffer->crsize += len;
        buffer->cursor += len;
    }
    return (buffer);
}

buffer_t*
insert_char_buffer(buffer_t* buffer, char c) {
    if (!buffer)
        { return (_BUFFER_NULL); }
    if (buffer->lcache) {
        if (_BUFFER_CACHE_FULL(buffer))
            { _flush_cache_buffer(buffer); }
        buffer->lcache[buffer->icache++] = c;
    } else {
        ++buffer->crsize;
        if (buffer->crsize >= buffer->slimit) {}
        (void)memmove(buffer->string + buffer->cursor + 1, buffer->string + buffer->cursor,
                                sizeof(char) * (buffer->cursor - (buffer->crsize - 1)));
        buffer->string[buffer->cursor] = c;
        ++buffer->cursor;
    }
    return (buffer);
}

buffer_t*
remove_size_buffer(buffer_t* buffer, size_t size) {
    if (!buffer)
        { return (_BUFFER_NULL); }
    if (buffer->lcache) {
        
    }
    if (buffer->cursor < size)
        { size = buffer->cursor; }
    if (size) {
        (void)memmove(buffer->string + (buffer->cursor - size),
                                buffer->string + buffer->cursor,
                                sizeof(char) * ((buffer->crsize - 1) - buffer->cursor));
        buffer->cursor -= size;
        buffer->crsize -= size;
        buffer->string[buffer->crsize] = '\0';
    }
    return (buffer);
}

void
_flush_cache_buffer(buffer_t* buffer) {
    if ((!buffer) && (!buffer->lcache))
        { return; }
    char* save_cache = buffer->lcache;
    buffer->lcache = NULL;
    insert_string_buffer(buffer, save_cache);
    (void)memset((void*)save_cache, 0, sizeof(char) * (_BUFFER_CACHE_DEFAULT + 1));
    buffer->lcache = save_cache;
    buffer->icache ^= buffer->icache;
}

