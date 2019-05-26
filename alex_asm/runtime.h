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
hash_t*     recompute_hash(hash_t const*);
exit_statut exec_command(char const*, list_t const*, hash_t const*, char const*, hash_t*);
void        call_function(hash_t*, char const*, list_t const*);

#endif /* _RUNTIME_H */
