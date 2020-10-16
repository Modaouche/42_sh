#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "edition.h"
#include "buffer.h"
#include "runtime.h"
#include "shell.h"
#include "utils.h"
#include "termcap.h"

int
main(int argc, char const* argv[], char const* envp[]) {
    hash_t* env = environment_hash(envp); 
    if (!env)
        { return (EXIT_FAILURE); }

    buffer_t* buffer = _BUFFER_NULL;
    bool eof_termcap;
    (void)_tgetent(&buffer, "SC", NULL, &eof_termcap);

    if (eof_termcap) {
        puts("\"TERMCAP\" Premature EOF");
        exit(EXIT_FAILURE);
    }

    printf("A = %s\n", _BUFFER_STRING(buffer));

    free_hash(env);
    exit(1);
/*
    line_t* edition = set_raw_mode();
    if (!edition)
        { return (EXIT_FAILURE); }
    else if (init_default_env(env)) {

    lexer_t* lex = make_lexer_from_file("shell.sh");
    token_type_t kind;
    while ((kind = next_token_lexer(lex)) != _EOF) {
        printf("%d\r\n", kind);
        if (kind == _TOKEN)
            { printf("%s\r\n", _BUFFER_STRING(lex->ctoken.lexeme)); }
    }
    free_lexer(lex);


    }


    bool backup;
    free_line(edition, &backup);

    return ((backup) ? (EXIT_SUCCESS) : (EXIT_FAILURE));
*/
}
