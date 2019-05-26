#include <stdio.h>
#include <string.h>
#include "runtime.h"
#include "hash.h"

int
main(int argc, char const* argv[], char const* envp[]) {
    hash_t* hash = environment_hash(envp);
    set_environment_hash(hash, "ASSEMBLY=FOVERER", NULL);
    iter_hash_t iter;
    init_iter_hash(hash, &iter);
    element_t* element;
    while ((element = next_iter_hash(&iter)))
        { printf("%s=%s\n", (*element)[0], (*element)[1]); }
    free_hash(hash);
}
