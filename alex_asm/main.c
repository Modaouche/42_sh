#include <stdio.h>
#include <string.h>

#include "buffer.h"
#include "shell.h"
#include "utils.h"

int
main(int argc, char const* argv[], char const* envp[]) {
    lexer_t* lex = make_lexer_from_file("shell.sh");
    int ctoken;
    while ((ctoken = next_token(lex)) != _EOF) {
        printf("TOKEN = %d\n", ctoken);
        if (ctoken == _TOKEN) {
            printf("%s\n", _BUFFER_STRING(_LEXER_TOKEN_LEXEME(lex)));
        }
    }
    free_lexer(lex);
}
