#include <stdio.h>
#include <string.h>

#include "edition.h"
#include "buffer.h"
#include "runtime.h"
#include "shell.h"
#include "utils.h"

int
main(int argc, char const* argv[], char const* envp[]) {
    buffer_t* buffer = read_file("a.out");
    write(1, _BUFFER_FULL_STRING(buffer), _BUFFER_SIZE(buffer));
    free_buffer(buffer);
    exit(1);

    line_t* edition = set_raw_mode();
    if (!edition)
        { return (EXIT_FAILURE); }
    hash_t* env = environment_hash(envp); 
    if (!env)
        { return (EXIT_FAILURE); }
    else if (init_default_env(env)) {
/*
    lexer_t* lex = make_lexer_from_file("shell.sh");
    token_type_t kind;
    while ((kind = next_token_lexer(lex)) != _EOF) {
        printf("%d\r\n", kind);
        if (kind == _TOKEN)
            { printf("%s\r\n", _BUFFER_STRING(lex->ctoken.lexeme)); }
    }
    free_lexer(lex);
*/

    }

    free_hash(env);

    bool backup;
    free_line(edition, &backup);

    return ((backup) ? (EXIT_SUCCESS) : (EXIT_FAILURE));
}
