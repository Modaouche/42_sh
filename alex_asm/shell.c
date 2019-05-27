#include <string.h>
#include <ctype.h>

#include "shell.h"
#include "utils.h"

lexer_t*
make_lexer_from_file(char const* file_path) {
    if (!file_path)
        { return (_LEXER_NULL); }
    /* TODO */
    return (_LEXER_NULL);
}

lexer_t*
make_lexer(char const* source) {
    if (!source)
        { return (_LEXER_NULL); }
    lexer_t* lexer = (lexer_t*)malloc(sizeof(*lexer));
    if (!lexer)
        { return (_LEXER_NULL); }
    (void)memset(lexer, 0, sizeof(*lexer));
    lexer->source = source;
    lexer->crmode = _TRECOGN;
    return (lexer); 
}

void
free_lexer(lexer_t const* lex) {
    if (!lex) {
        if (lex->ctoken.lexeme)
            { free((void*)lex->ctoken.lexeme); }
        free((void*)lex->source);
        free((void*)lex);
    }
}

typedef int (*_lex_pred_t)(int);

static int
_is_not_newline(int _char) {
    return (_char != 0x0A);
}

static void
_skip_predicate(char const** source, _lex_pred_t pred) {
    while ((**source) && (*pred)(**source))
        { ++(*source); }
}

#define _IS_WORD(_char)     (((_char) != ';') || ((_char) != '!') || ((_char) != '<')\
                                || ((_char) != '>') || ((_char) != '&') || ((_char) != '|'))

static char const*
_get_next_word(char const** body, char const* prefix) {
    bool escape = false;
    bool dquote = false;
    bool squote = false;
    char register _char = 0x01;
    while (_char) { 
        _char = **body;
        if ((_IS_WORD(_char) || (escape || dquote || squote)))
            { break; }
        else if (isblank(_char))
            { break; }

        if (!escape) {
            if (_char == '\'' && !dquote)
                { squote ~= squote; }
            else if (_char == '"' && !squote)
                { dquote ~= dquote; }
            else if (_char == '\\' && !squote)
                { escape = true; }
        } else
            { escape = false; }
    /* TODO */
}

#ifdef _LEX_LOOKUP

#endif /* _LEX_LOOKUP */

token_type_t
next_token(lexer_t* lex) {
    if (!lex)
        { return (_ERROR); }
    if (lex->ctoken.lexeme)
        { free((void*)lex->ctoken.lexeme); }
    lex->ctoken.lexeme = NULL;
    _skip_predicate(&lex->source, &isblank);
    char const* begin = lex->source;
    while (*lex->source) {
        char register char_1 = lex->source[0];
        #ifdef _LEX_LOOKUP
            /* TODO */
        #else
            char register char_2 = lex->source[1];
            switch (char_1) {
                case ';':
                case '!':   lex->ctoken.ndtype = char_1;
                            break;
                case '&':   lex->ctoken.ndtype = '&';
                            if (char_2 == '&') {
                                lex->ctoken.ndtype = AND_IF;
                                ++lex->source;
                            }
                            break;

                case '|':   lex->ctoken.ndtype = '|';
                            if (char_2 == '|') {
                                lex->ctoken.ndtype = OR_IF;
                                ++lex->source;
                            }
                            break;

                case '<':   lex->ctoken.ndtype = '<';
                            ++lex->source;
                            switch (char_2) {
                                case '&': lex->ctoken.ndtype = LESSAND; break;
                                case '<': lex->ctoken.ndtype = DLESS; break;
                                case '>': lex->ctoken.ndtype = LESSGREAT;
                                    if (lex->source[1] == '-') {
                                        lex->ctoken.ndtype = DLESSDASH;
                                        ++lex->source;
                                    }
                                    break;
                                default:  --lex->source;
                            }
                            break;

                case '>':   lex->ctoken.ndtype = '>';
                            ++lex->source;
                            switch (char_2) {
                                case '&': lex->ctoken.ndtype = GREATAND; break;
                                case '>': lex->ctoken.ndtype = DGREAT; break;
                                case '|': lex->ctoken.ndtype = CLOBBER; break;
                                default:  --lex->source;  
                            } 
                            break;
                
                #ifdef __GNUC__
                    case '0' ... '9': 
                #else
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                #endif /* __GNUC__ */
                        lex->ctoken.ndtype = _TOKEN;
                        _skip_predicate(&lex->source, &isdigit);
                        if ((*lex->source == '<') || (*lex->source == '>')) {
                            lex->ctoken.ndtype = IO_NUMBER;
                            lex->ctoken.io_num = (size_t)strtol(begin, NULL, 0x0A);
                        } else {
                            // TODO
                            //_skip_predicate(&lex->source,
                        }    
                        break;

                case '#':   _skip_predicate(&lex->source, &_is_not_newline);
                            break;
                    
                default: ;
                        
            }
        #endif /* _LEX_LOOKUP */
        ++lex->source;
    }
    if (!*lex->source) {
    }
}

token_type_t
peek_token(lexer_t* lex) {
    if (!lex)
        { return (_ERROR); }
    if (!lex->havepk) {

    }
    return (lex->ctoken.ndtype);
}

