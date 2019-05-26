#ifndef _RUNTIME_H
#define _RUNTIME_H

#include "hash.h"

typedef struct {
    char const* command;
    char const* path_fl;
} _command_node_t;

typedef struct {
    char const* lvalue;
    char const* rvalue;
} _variable_env_t;

typedef int exit_statut;

hash_t*     environment_hash(char const*[]);
hash_t*     set_environment_hash(hash_t*, char const*, bool*);

exit_statut exec_command(char const*, list_t const*, hash_t const*, hash_t*);
void        set_variable(hash_t*, char const*, char const*);
void        call_function(hash_t*, char const*, list_t const*);

#endif /* _RUNTIME_H */
