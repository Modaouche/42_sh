#include <stdio.h>
#include <string.h>

#include "buffer.h"
#include "shell.h"
#include "utils.h"

int
main(int argc, char const* argv[], char const* envp[]) {
    lexer_t* lex = make_lexer_from_file("shell.sh");
    printf("%d\n", next_token_lexer(lex));
    printf("%s\n", _BUFFER_FULL_STRING(lex->ctoken.lexeme));
    free_lexer(lex);
}
