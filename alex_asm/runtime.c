#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#include "runtime.h"
#include "utils.h"

static void
_del_variable_env(element_t variable_env_t) {
    free((void*)((_variable_env_t*)variable_env_t)->lvalue);
    free((void*)((_variable_env_t*)variable_env_t)->rvalue);
}

static element_t
_cpy_variable_env(element_t variable_env_t) {
    element_t element = (element_t)malloc(sizeof(generic_t) * 3);
    if (!element)
        { return (_GENERIC_NULL); }
    if (!(element[0] = (generic_t)strdup(variable_env_t[0])))
        { return (_GENERIC_NULL); }
    else if (!(element[1] = (generic_t)strdup(variable_env_t[1]))) {
        free(element[0]);
        return (_GENERIC_NULL);
    }
    element[2] = variable_env_t[2];
    return (element);
}

static bool
_split_environment(char const* env_line, char** lvalue, char** rvalue) {
    if (!env_line)
        { return (false); }
    if (lvalue)
        { (*lvalue) = NULL; }
    if (rvalue)
        { (*rvalue) = NULL; }
    char const* split = strchr(env_line, '=');
    size_t len = strlen(env_line);
    if (split && (split != env_line)) {
        if (lvalue) {
            size_t size_lvalue = (split - env_line);
            (*lvalue) = (char*)malloc(sizeof(char) * (size_lvalue + 1));
            if (!(*lvalue))
                { return (false); }
            (*lvalue)[size_lvalue] = '\0';
            (void)memcpy((*lvalue), env_line, size_lvalue);
        }
        if (rvalue) {
            size_t size_rvalue = (len - (split - env_line + 1));
            (*rvalue) = (char*)malloc(sizeof(char) * (size_rvalue + 1));
            if (!(*rvalue)) {
                if (lvalue)
                    { free((void*)(*lvalue)); }
                return (false);
            }
            (*rvalue)[size_rvalue] = '\0';
            (void)memcpy((*rvalue), split+1, size_rvalue);
        }
    }
    return (true);
}

hash_t*
environment_hash(char const* envp[]) {
    if (!envp)
        { return (_HASH_NULL); }
    hash_t* hash = make_hash((_selector_t)&hash_string, 0x20,
                                            &_del_variable_env,
                                            &_cpy_variable_env);
    if (!hash)
        { return (_HASH_NULL); }

    char* lvalue;
    char* rvalue;
    bool success = true;
    for (size_t i = 0; envp[i]; ++i) {
        if (!_split_environment(envp[i], &lvalue, &rvalue)) {
            success = false;
            break;
        }
        if ((lvalue && rvalue) && (!insert_hash(hash, 3, 0,
                                        (void*)lvalue, (void*)rvalue, (void*)true))) {
            free((void*)lvalue);
            free((void*)rvalue);
            success = false;
            break;
        }
    }
    if (!success) {
        free_hash(hash);
        return (_HASH_NULL);
    }
    return (hash);
}

static bool
_compare_environment(_variable_env_t* element, char const* env_line) {
    char const* split = strchr(env_line, '=');
    if (!split)
        { return (!strncmp(element->lvalue, env_line, (split - env_line))); }
    return (!strcmp(element->lvalue, env_line));
}

static hash_t*
_set_environment_value(hash_t* hash, char const* lvalue,
                                    char const* rvalue, bool _export, bool* use_path) {
    element_t element = lookup_hash(hash, (_elt_comp_t)&_compare_environment,
                                          (generic_t)lvalue);
    if (!element) {
        if (!insert_hash(hash, 3, 0, (void*)lvalue, (void*)rvalue, (void*)_export))
            { return (_HASH_NULL); }
    } else {
        free((void*)((_variable_env_t*)element)->rvalue);
        ((_variable_env_t*)element)->rvalue = rvalue;
    }
    if (use_path) {
        (*use_path) = false;
        if (!strcmp("PATH", lvalue))
            { (*use_path) = true; }
    }
    return (hash);
}

hash_t*
init_default_env(hash_t* hash) {
    static char const* check_value[] = { "PS1", "PWD", "SHLVL", NULL };
    if (!hash)
        { return (_HASH_NULL); }
    for (size_t i = 0; check_value[i]; ++i) {
        element_t element = lookup_hash(hash,   (_elt_comp_t)&_compare_environment,
                                                (generic_t)check_value[i]);
        if (!element) {
            char const* rvalue = NULL;
            switch (i) {
                case 0: rvalue = strdup("$ ");      break;
                case 1: rvalue = getcwd(NULL, 0);   break;
                case 2: rvalue = strdup("1");       break;
            }
            if ((!rvalue) || (!_set_environment_value(hash,
                                        check_value[i], rvalue, true, NULL))) {
                free((void*)rvalue);
                return (_HASH_NULL);
            }
        }
    }
    return (hash);
}

hash_t*
set_environment_hash(hash_t* hash, char const* env_line, bool _export, bool* use_path) {
    if (!hash)
        { return (_HASH_NULL); }
    if (!env_line || !strchr(env_line, '='))
        { return (hash); }
    element_t element = lookup_hash(hash,   (_elt_comp_t)&_compare_environment,
                                            (generic_t)env_line);
    char* lvalue;
    char* rvalue;
    if (!element) {
        if (!_split_environment(env_line, &lvalue, &rvalue))
            { return (_HASH_NULL); }
        if (!insert_hash(hash, 3, 0, (void*)lvalue, (void*)rvalue, (void*)_export)) {
            free((void*)lvalue);
            free((void*)rvalue);
            return (_HASH_NULL);
        }
    } else {
        if (!_split_environment(env_line, NULL, &rvalue))
            { return (_HASH_NULL); }
        free((void*)((_variable_env_t*)element)->rvalue);
        ((_variable_env_t*)element)->rvalue = rvalue;
    }
    if (use_path) {
        (*use_path) = false;
        if (!strncmp("PATH", env_line, 4))
            { (*use_path) = true; }
    }
    return (hash);
}

static size_t
#ifdef _ASSEMBLY
__attribute__((naked))
#endif /* _ASSEMBLY */
_count_occurence(
#ifdef _ASSEMBLY
__attribute__((unused))
#endif /* _ASSEMBLY */
char const* line,
#ifdef _ASSEMBLY
__attribute__((unused))
#endif /* _ASSEMBLY */
char const* sep) {
    #ifdef _ASSEMBLY
        #if defined(__x86_64__) // system v
            __asm__("xchgq   %rdi, %rsi");
            __asm__("xorb    %al, %al");
            __asm__("xorq    %rcx, %rcx");
            __asm__("notq    %rcx");
            __asm__("movq    %rdi, %r8");
            __asm__("cld");
            __asm__("repnz   scasb");
            __asm__("incq    %rcx"); 
            __asm__("notq    %rcx");
            __asm__("movq    %rcx, %rdx");
            __asm__("xorb    %r9b, %r9b");
            __asm__(".BEG:");
            __asm__("movb    (%rsi), %al");
            __asm__("testb   %al, %al");
            __asm__("jz      .END");
            __asm__("movq    %r8, %rdi");
            __asm__("movq    %rdx, %rcx");
            __asm__("repnz   scasb");
            __asm__("setzb   %al");
            __asm__("addb    %al, %r9b");
            __asm__("incq    %rsi");
            __asm__("jmp     .BEG");
            __asm__(".END:");
            __asm__("movzx   %r9b, %rax");
            __asm__("retq");
        #elif defined(__i386__) // cdecl
            // TODO
        #else
            #error "UNABLE TO TARGET AN ARCHITECTURE"
        #endif  /* defined(__x86_64__) */
    #else
        size_t count = 0;
        for (size_t i = 0; line[i]; ++i) {
            for (size_t j = 0; sep[j]; ++j) {
                if (line[i] == sep[j]) {
                    ++count;
                    break;
                }
            }
        }
        return (count);
    #endif /* _ASSEMBLY */
}

static int
_fill_entry(char** array, size_t index, char const* last, char const* iter) {
    size_t size_str = iter - last;
    array[index] = (char*)malloc(sizeof(*array[index]) * (size_str + 1));
    if (!array[index]) {
        for (size_t i = 0; i < index; ++i)
            { free((void*)array[i]); }
        free((void*)array);
        return (-1);
    }
    array[index][size_str] = '\0';
    (void)memcpy((void*)array[index], (void*)last, size_str);
    return (0);
}

static char**
_split_array(char const* line, char const* sep) {
    if (!line || !sep)
        { return (NULL); }
    size_t count = _count_occurence(line, sep);
    size_t size = (count) ? (strlen(line) - count) : (1);
    char** array = (char**)malloc(sizeof(*array) * (size + 1));
    if (!array)
        { return (NULL); }
    (void)memset((void*)array, 0, sizeof(*array) * (size + 1));
    char const* last = line;
    char const* iter;
    size_t index = 0;
    while ((iter = strpbrk(line, sep))) {
        if (last != iter) {
            if (_fill_entry(array, index, last, iter))
                { return (NULL); }
            ++index;
        }
        line = iter + 1;
        last = line;
    }
    line = strchr(line, '\0');
    if (*last && _fill_entry(array, index, last, line))
        { return (NULL); }
    return (array);
}

hash_t*
recompute_hash(hash_t const* envp) {
    if (!envp)
        { return (_HASH_NULL); }
    element_t element = lookup_hash(envp, (_elt_comp_t)&_compare_environment, "PATH");
    if (!element)
        { return (_HASH_NULL); }
    char const* path_value = ((_variable_env_t*)element)->rvalue;
    if (!path_value || !*path_value)
        { return (_HASH_NULL); }
    char** target_dir = _split_array(path_value, ":");
    if (!target_dir)
        { return (_HASH_NULL); }
    for (size_t i = 0; target_dir[i]; ++i) {
        DIR* directory;
        struct dirent* entry;
        directory = opendir(target_dir[i]);
        if (!directory)
            { break; }
        while ((entry = readdir(directory))) {
            /* TODO */
        }
        closedir(directory);
    }
    for (size_t i = 0; target_dir[i]; ++i)
        { free((void*)target_dir[i]); }
    free((void*)target_dir);
    return (_HASH_NULL);
}

/*
char const*
expand_variable(char const* target, hash_t const* env) {
}
*/

bool
expand_token_tilde(buffer_t* buffer) {

}

bool
expand_token(buffer_t* buffer, hash_t const* hash) {

}

exit_statut
exec_command(char const* command, list_t const* params, hash_t const* envp, 
                                  char const* path_val, hash_t* cpath) {
    if (!command)
        { return (EXIT_FAILURE); }
    return (EXIT_SUCCESS);
}
