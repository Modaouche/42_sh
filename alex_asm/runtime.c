#include <stdlib.h>
#include <string.h>
#include "runtime.h"

static void
_del_variable_env(element_t variable_env_t) {
    free((void*)((_variable_env_t*)variable_env_t)->lvalue);
    free((void*)((_variable_env_t*)variable_env_t)->rvalue);
}

static element_t
_cpy_variable_env(element_t variable_env_t) {
    element_t element = (element_t)malloc(sizeof(generic_t) * 2);
    if (!element)
        { return (_GENERIC_NULL); }
    if (!(element[0] = (generic_t)strdup(variable_env_t[0])))
        { return (_GENERIC_NULL); }
    else if (!(element[1] = (generic_t)strdup(variable_env_t[1]))) {
        free(element[0]);
        return (_GENERIC_NULL);
    }
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
    char* lvalue;
    char* rvalue;
    bool success = true;
    for (size_t i = 0; envp[i]; ++i) {
        if (!_split_environment(envp[i], &lvalue, &rvalue)) {
            success = false;
            break;
        }
        if ((lvalue && rvalue) && !insert_hash(hash, 2, 0, (void*)lvalue, (void*)rvalue)) {
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
        { return (false); }
    return (!strncmp(element->lvalue, env_line, (split - env_line)));
}

hash_t*
set_environment_hash(hash_t* hash, char const* env_line, bool* use_path) {
    if (!hash)
        { return (_HASH_NULL); }
    element_t element = lookup_hash(hash,   (_elt_comp_t)&_compare_environment,
                                            (generic_t)env_line);
    char* lvalue;
    char* rvalue;
    if (!element) {
        if (!_split_environment(env_line, &lvalue, &rvalue))
            { return (_HASH_NULL); }
        if (!insert_hash(hash, 2, 0, (void*)lvalue, (void*)rvalue)) {
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
