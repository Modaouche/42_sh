#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>

#include "shell.h"
#include "utils.h"

#define _CHUNK_SIZE (255)

lexer_t*
make_lexer_from_file(char const* file_path) {
    if (!file_path)
        { return (_LEXER_NULL); }
    int fd = open(file_path, O_RDONLY);
    if (fd == -1)
        { return (_LEXER_NULL); }
    buffer_t* buffer = make_buffer(true);
    char chunk[_CHUNK_SIZE] = {};
    int rd;
    while ((rd = read(fd, chunk, _CHUNK_SIZE))) {
        bool failure = false;
        if (rd != -1) {
            chunk[rd] = '\0';
            if (!insert_string_buffer(buffer, chunk))
                { failure = true; }
        }
        else
            { failure = true; }
        if (failure) {
            free_buffer(buffer);
            return (_LEXER_NULL);
        }
    }
    lexer_t* lexer = make_lexer(_BUFFER_STRING(buffer));
    free_buffer(buffer);
    return (lexer);
}

lexer_t*
make_lexer(char const* source) {
    if (!source)
        { return (_LEXER_NULL); }
    lexer_t* lexer = (lexer_t*)malloc(sizeof(*lexer));
    if (!lexer)
        { return (_LEXER_NULL); }
    (void)memset(lexer, 0, sizeof(*lexer));
    lexer->source = strdup(source);
    if (!lexer->source) {
        free((void*)lexer);
        return (_LEXER_NULL);
    }
    lexer->crmode = _TRECOGN;
    return (lexer); 
}

void
free_lexer(lexer_t const* lex) {
    if (lex) {
        if (lex->ctoken.ndtype == _TOKEN)
            { free_buffer(lex->ctoken.lexeme); }
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

static void
_get_next_operator(lexer_t* lex) {
    if (!*lex->source)
        { return; }
    char register char_1 = lex->source[0];
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
    }
}

#ifdef _LEX_LOOKUP

#endif /* _LEX_LOOKUP */

token_type_t
next_token(lexer_t* lex) {
    if (!lex)
        { return (_ERROR); }
    else if ((lex->ctoken.ndtype == _TOKEN) && (lex->ctoken.lexeme))
        { free_buffer(lex->ctoken.lexeme); }

    bool escape = false;
    bool dquote = false;
    bool squote = false;

    buffer_t* current_word = _BUFFER_NULL;
    bool delim_word = false;

    char const* begin = lex->source;
    _skip_predicate(&lex->source, &isblank);

    if (!*lex->source)
        { return ((lex->ctoken.ndtype = _EOF)); }
    while (*lex->source) {
        bool save_escape = escape;
        escape = false;
        char register _char = lex->source[0];
        if (isblank(_char) && (!(escape || dquote || squote)))
            { break; }
        #ifdef _LEX_LOOKUP
            /* TODO */
        #else
            switch (_char) {
                case 0x0A:
                    printf("NEW_LINE\n");
                    if (current_word) {
                        if (save_escape)
                            { remove_size_buffer(current_word, 1); }
                        else if (!(dquote || squote))
                            { delim_word = true; }
                    } else
                        { lex->ctoken.ndtype = NEWLINE; }
                    break;

                case ';': case '!': case '&':   
                case '|': case '<': case '>': 
                    if (!(save_escape || dquote || squote))
                        { _get_next_operator(lex); }
                    break;

                #ifdef __GNUC__
                    case '0' ... '9': 
                #else
                    case '0': case '1': case '2': case '3': case '4':
                    case '5': case '6': case '7': case '8': case '9':
                #endif /* __GNUC__ */
                        if (!current_word) {
                            lex->ctoken.ndtype = _TOKEN;
                            _skip_predicate(&lex->source, &isdigit);
                            if ((*lex->source == '<') || (*lex->source == '>')) {
                                lex->ctoken.ndtype = IO_NUMBER;
                                lex->ctoken.io_num = (size_t)strtol(begin, NULL, 0x0A); 
                                delim_word = true;
                            } else {
                                current_word = make_buffer(true);
                                insert_string_size_buffer(current_word,
                                                    begin, (lex->source - begin));
                            }
                        }    
                        break;

                case '#':   if (!current_word) {
                                _skip_predicate(&lex->source, &_is_not_newline);
                                continue;
                            }
                            else
                                { delim_word = true; }
                            break;
                    
                default:    if (!current_word) {
                                current_word = make_buffer(true);
                                lex->ctoken.ndtype = _TOKEN;
                            }
                            if (!save_escape) {
                                if ((_char == '\'') && (!dquote))
                                    { squote = ~squote; }
                                else if ((_char == '"') && (!squote))
                                    { dquote = ~dquote; }
                                else if ((_char == '\\') && (!squote))
                                    { escape = true; }
                            }
            }
        #endif /* _LEX_LOOKUP */
        if (!delim_word)
            { ++lex->source; }
        if ((!current_word) || (delim_word))
            { break; }
        else if ((_char != 0x0A) || (squote))
            { insert_char_buffer(current_word, _char); }
    }
    if (current_word)
        { lex->ctoken.lexeme = current_word; }
    return (lex->ctoken.ndtype);
}

token_type_t
peek_token(lexer_t* lex) {
    if (!lex)
        { return (_ERROR); }
    if (!lex->havepk) {
    }
    return (lex->ctoken.ndtype);
}

