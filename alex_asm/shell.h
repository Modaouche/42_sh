#ifndef _SHELL_H
#define _SHELL_H

#include <stdlib.h>
#include <stdbool.h>

#define _LEXER_NULL             (NULL)
#define _LEXER_SOURCE(_)        ((char const*)(_)->source)
#define _LEXER_TOKEN_TYPE(_)    ((token_type_t)(_)->ctoken->ndtype)
#define _LEXER_TOKEN_LEXEME(_)  ((char const*)(_)->ctoken->lexeme)
#define _LEXER_FILENO(_)        ((size_t)(_)->fileno)
#define _LEXER_MODE(_)          ((_mode_t)(_)->mode)

typedef enum {
    WORD                = 0x00,
    ASSIGNMENT_WORD     = 0x01,
    NAME                = 0x02,
    NEWLINE             = 0x03,
    IO_NUMBER           = 0x04,
    AND_IF              = 0x05,
    OR_IF               = 0x06,
    DSEMI               = 0x07,
    DLESS               = 0x07,
    DGREAT              = 0x08,
    LESSAND             = 0x09,
    GREATAND            = 0x0A,
    LESSGREAT           = 0x0B,
    DLESSDASH           = 0x0C,
    CLOBBER             = 0x0D,
    If                  = 0x0E,
    Then                = 0x0F,
    Else                = 0x10,
    Elif                = 0x11,
    Fi                  = 0x12,
    Do                  = 0x13,
    Done                = 0x14,
    Case                = 0x15,
    Esac                = 0x16,
    While               = 0x17,
    Until               = 0x18,
    For                 = 0x19,
    Lbrace              = 0x1A,
    Rbrace              = 0x1B,
    Bang                = 0x1C,
    In                  = 0x1D,
    _EOF                =   -1,
    _ERROR              =   -2,
    _TOKEN              =   -3,
} token_type_t;

typedef struct {
    token_type_t    ndtype;
    size_t          lineno;
    union {
        char const*     lexeme;
        size_t          io_num;
    };
} token_t;

typedef enum {
    _TRECOGN=0xC0,
    _HEREDOC=0xDE,
} _mode_t;

typedef struct {
    /* lexer_t composite must free the souce given by the caller  */
    char const*     source;
    token_t         ctoken;
    size_t          lineno;
    bool            havepk;
    _mode_t         crmode;
} lexer_t;

/* TODO SHELL SCRIPT */
lexer_t*        make_lexer_from_file(char const*)   __attribute__((nothrow));
lexer_t*        make_lexer(char const*)             __attribute__((nothrow));
void            free_lexer(lexer_t const*)          __attribute__((nothrow));
token_type_t    next_token(lexer_t*)                __attribute__((nothrow));
token_type_t    peek_token(lexer_t*)                __attribute__((nothrow));

#endif /* _SHELL_H */
