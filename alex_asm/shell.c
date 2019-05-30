#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

#include "shell.h"
#include "utils.h"

#define _CHUNK_SIZE (255)

static lexer_t*
_make_lexer_from_buffer(buffer_t* buffer) {
    if (!buffer)
        { return (_LEXER_NULL); }
    _BUFFER_SET_CURSOR(buffer, 0);
    lexer_t* lexer = (lexer_t*)malloc(sizeof(*lexer));
    if (!lexer)
        { return (_LEXER_NULL); }
    (void)memset(lexer, 0, sizeof(*lexer));
    lexer->source = buffer;
    lexer->ctoken.ndtype  = _NONE;
    lexer->crmode = _TRECOGN;
    return (lexer); 
}

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
            if (rd != strlen(chunk))
                { /* TODO \0 IN INPUT BITCH */ }
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
    lexer_t* lexer = _make_lexer_from_buffer(buffer);
    if (!lexer)
        { free_buffer(buffer); }
    return (lexer);
}

lexer_t*
make_lexer(char const* source) {
    if (!source)
        { return (_LEXER_NULL); }
    buffer_t* buffer = make_buffer(false);
    if (!insert_string_buffer(buffer, source)) {
        free_buffer(buffer);
        return (_LEXER_NULL);
    }
    lexer_t* lexer = _make_lexer_from_buffer(buffer);
    if (!lexer)
        { free_buffer(buffer); }
    return (lexer);
}

void
free_token(token_t const* token) {
    if (token) {
        if (token->ndtype == _TOKEN)
            { free_buffer(token->lexeme); }
        free((void*)token);
    }
}

void
free_lexer(lexer_t const* lex) {
    if (lex) {
        if (lex->ctoken.ndtype == _TOKEN)
            { free_buffer(lex->ctoken.lexeme); }
        free_buffer(lex->source);
        free((void*)lex);
    }
}

typedef int     (*_lex_pred_t)(int);
typedef void    (*_tokenset_t)(lexer_t*);

static int
_is_not_newline(int _char) {
    return (_char != 0x0A);
}

static void
_skip_predicate(buffer_t* source, _lex_pred_t pred) {
    while ((!_BUFFER_EOF(source)) && ((*pred)(_BUFFER_CURSOR_CHAR(source))))
        { _BUFFER_FORWARD_CURSOR(source); }
}

static void
_lexer_operator(lexer_t* lex) {
    char register char_1 = _BUFFER_CURSOR_CHAR(lex->source);
    char register char_2 = _BUFFER_STRING(lex->source)[1];
    switch (char_1) {
        case ';':
        case '!':   lex->ctoken.ndtype = char_1;
                    break;
        case '&':   lex->ctoken.ndtype = '&';
                    if (char_2 == '&') {
                        lex->ctoken.ndtype = AND_IF;
                        _BUFFER_FORWARD_CURSOR(lex->source);
                    }
                    break;

        case '|':   lex->ctoken.ndtype = '|';
                    if (char_2 == '|') {
                        lex->ctoken.ndtype = OR_IF;
                        _BUFFER_FORWARD_CURSOR(lex->source);
                    }
                    break;

        case '<':   lex->ctoken.ndtype = '<';
                    _BUFFER_FORWARD_CURSOR(lex->source);
                    switch (char_2) {
                        case '&':   lex->ctoken.ndtype = LESSAND; break;
                        case '<':   lex->ctoken.ndtype = DLESS; break;
                        case '>':   lex->ctoken.ndtype = LESSGREAT;
                            if (_BUFFER_STRING(lex->source)[1] == '-') {
                                lex->ctoken.ndtype = DLESSDASH;
                                _BUFFER_FORWARD_CURSOR(lex->source);
                            }
                            break;
                        default:    _BUFFER_REVERSE_CURSOR(lex->source);
                    }
                    break;

        case '>':   lex->ctoken.ndtype = '>';
                    _BUFFER_FORWARD_CURSOR(lex->source);
                    switch (char_2) {
                        case '&':   lex->ctoken.ndtype = GREATAND; break;
                        case '>':   lex->ctoken.ndtype = DGREAT; break;
                        case '|':   lex->ctoken.ndtype = CLOBBER; break;
                        default:    _BUFFER_REVERSE_CURSOR(lex->source); 
                    } 
                    break;
    }
}

static void
_lexer_newline(lexer_t* lex) {
    lex->ctoken.ndtype = NEWLINE;
    ++(lex->lineno);
}

static void
_lexer_comment(lexer_t* lex) {
    _skip_predicate(lex->source, &_is_not_newline);
}

static void
_lexer_token_squote(lexer_t* lex) {
    if (!(_BUFFER_CURSOR_CHAR(lex->source) != '\''))
        { return; }
    _BUFFER_FORWARD_CURSOR(lex->source);
    while ((!_BUFFER_EOF(lex->source)) && (_BUFFER_CURSOR_CHAR(lex->source) != '\''))
        { _BUFFER_FORWARD_CURSOR(lex->source); }
    if (_BUFFER_EOF(lex->source))
        { lex->lerror |= UNBALANCE_SQUOTE; }
}

static void
_lexer_token_bctick(lexer_t* lex) {
    if (!(_BUFFER_CURSOR_CHAR(lex->source) != '`'))
        { return; }
    _BUFFER_FORWARD_CURSOR(lex->source);
    bool escape = false;
    while (!_BUFFER_EOF(lex->source)) {
        if (escape)
            { escape = false; }
        else {
            if (_BUFFER_CURSOR_CHAR(lex->source) == '`')
                { break; }
            else if (_BUFFER_CURSOR_CHAR(lex->source) == '\\')
                { escape = true; }
        }
        _BUFFER_FORWARD_CURSOR(lex->source);
    }
    if (_BUFFER_EOF(lex->source))
        { lex->lerror |= UNBALANCE_BCTICK; }
}

static int
_is_identifier(char c) {
    return ((isalnum(c)) || (c == '_'));
}

static void _lexer_token_dquote(lexer_t*, size_t);

#define _DEPTH_START    (0x00)
#define _DEPTH_LIMIT    (0xFF)

static void
_lexer_token_dollar(lexer_t* lex, size_t depth) {
    if (!(_BUFFER_CURSOR_CHAR(lex->source) != '$'))
        { return; }
    _BUFFER_FORWARD_CURSOR(lex->source);
    bool param_expand = false;
    bool command_subs = false;
    bool arith_expand = false;

    bool escape = false;
    bool braces = false;
    if (_BUFFER_CURSOR_CHAR(lex->source) == '(') {
        _BUFFER_FORWARD_CURSOR(lex->source);
        if (_BUFFER_STRING(lex->source)[1] == '(') { 
            _BUFFER_FORWARD_CURSOR(lex->source);
            arith_expand = true;
        } else
            { command_subs = true; }
    } else {
        param_expand = true;
        switch (_BUFFER_CURSOR_CHAR(lex->source)) {
            case '@': case '*': case '#': case '?':
            case '-': case '$': case '!': case '0':
            #ifdef __GNUC__
                case '1' ... '9':
            #else
                case '1': case '2': case '3': case '4':
                case '5': case '6': case '7': case '8':
                case '9':
            #endif /* __GNUC__ */
                        return;
            case '{':   _BUFFER_FORWARD_CURSOR(lex->source);
                        braces = true;
                        break;
        }
    }
    while (!_BUFFER_EOF(lex->source)) {
        if ((param_expand) && (!braces)) {
            if (!_is_identifier(_BUFFER_CURSOR_CHAR(lex->source))) {
                _BUFFER_REVERSE_CURSOR(lex->source);
                return;
            }
        }
        if (escape)
            { escape = false; }
        else {
            char register _char = _BUFFER_CURSOR_CHAR(lex->source);
            if ((param_expand) && (_char == '}'))
                { return; }
            else if ((!param_expand) && (_char ==  ')')) {
                if (command_subs)
                    { return; }
                else if (_BUFFER_STRING(lex->source)[1] == ')') {
                    _BUFFER_FORWARD_CURSOR(lex->source);
                    return;
                }
            }
            else {
                switch (_char) {
                    case '\\':  escape = true; break;
                    case '\'':  _lexer_token_squote(lex); break;
                    case '`':   _lexer_token_bctick(lex); break;
                    case '"':   _lexer_token_dquote(lex, depth + 1); break;
                    case '$':   _lexer_token_dollar(lex, depth + 1); break;
                }
            }
        }
        _BUFFER_FORWARD_CURSOR(lex->source);
    }
    if (_BUFFER_EOF(lex->source)) {
        if (param_expand) {}
        else if (command_subs) {}
        else {}
    }
}

static void
_lexer_token_dquote(lexer_t* lex, size_t depth) {
    if (depth > _DEPTH_LIMIT) {
        lex->edepth = true;
        return;
    }
    if (!(_BUFFER_CURSOR_CHAR(lex->source) != '"'))
        { return; }
    _BUFFER_FORWARD_CURSOR(lex->source);
    bool escape = false;
    while (!_BUFFER_EOF(lex->source)) {
        if (escape)
            { escape = false; }
        else {
            if (_BUFFER_CURSOR_CHAR(lex->source) == '"')
                { return; }
            switch (_BUFFER_CURSOR_CHAR(lex->source)) {
                case '\\':  escape = true; break;
                case '`':   _lexer_token_bctick(lex); break;
                case '$':   _lexer_token_dollar(lex, depth + 1); break;
            }
        } 
        _BUFFER_FORWARD_CURSOR(lex->source);
    }
    if (_BUFFER_EOF(lex->source))
        { lex->lerror |= UNBALANCE_DQUOTE; }
}

#define _TOKEN_FIRST            "\n;!&|<>#"
#define _IS_WORD(_)             ((_) && ((!isblank(_)) && (!strchr(_TOKEN_FIRST, (_)))))

static void
_lexer_token(lexer_t* lex) {
    buffer_t* current_word = make_buffer(true);
    if (!current_word)
        { return; }
    bool escape = false;
    while (_IS_WORD(_BUFFER_CURSOR_CHAR(lex->source)) || (escape)) {
        bool _write = true;
        if (escape) {
            if (_BUFFER_CURSOR_CHAR(lex->source) == 0x0A) {
                remove_size_buffer(current_word, 1);
                _write = false;
            }   
            escape = false;
        } else {
            switch (_BUFFER_CURSOR_CHAR(lex->source)) {
                case '\\':  escape = true; break;
                case '\'':  _lexer_token_squote(lex); break;
                case '`':   _lexer_token_bctick(lex); break;
                case '"':   _lexer_token_dquote(lex, _DEPTH_START); break;
                case '$':   _lexer_token_dollar(lex, _DEPTH_START); break;
            }
        }
        if (_write)
            { _BUFFER_INSERT_CHAR(current_word, _BUFFER_CURSOR_CHAR(lex->source)); }
        _BUFFER_FORWARD_CURSOR(lex->source);
    }
    _BUFFER_SET_CURSOR(current_word, 0);
    if (_BUFFER_SIZE(current_word)) {
        lex->ctoken.ndtype = _TOKEN;
        lex->ctoken.lexeme = current_word;
    } else
        { free_buffer(current_word); }
}

#ifdef _LEX_LOOKUP

static _tokenset_t
_lexer_lookup[UCHAR_MAX] = {
    #ifndef __GNUC__
    #else
        [0x0A]=&_lexer_newline,
        [0x21]=&_lexer_operator, 
        [0x23]=&_lexer_comment,
        [0x26]=&_lexer_operator,
        [0x3B]=&_lexer_operator,
        [0x3C]=&_lexer_operator,
        [0x3E]=&_lexer_operator,
        [0x7C]=&_lexer_operator,
    #endif /* __GNUC__ */
};

#endif /* _LEX_LOOKUP */


token_type_t
next_token_lexer(lexer_t* lex) {
    if (!lex)
        { return (_ERROR); }
    else if (lex->ctoken.ndtype == _TOKEN)
        { free_buffer(lex->ctoken.lexeme); }
    lex->ctoken.ndtype = _NONE;
    _lexer_token(lex);
    return (lex->ctoken.ndtype);
}
#if 0

    size_t begin_cur = _BUFFER_GET_CURSOR(lex->source);
    _skip_predicate(lex->source, &isblank);

    if (_BUFFER_EOF(lex->source))
        { return ((lex->ctoken.ndtype = _EOF)); }
    while (!_BUFFER_EOF(lex->source)) {
        bool save_escape = escape;
        escape = false;

        bool save_reeval = reeval;
        reeval = false;

        char register _char = _BUFFER_CURSOR_CHAR(lex->source);
        if (isblank(_char)) {
            if (save_reeval) {
                _skip_predicate(&lex->source, &isblank);
                if (!*lex->source) {
                    free_buffer(current_word);
                    return ((lex->ctoken.ndtype = _EOF));
                }
            }
            else if (!(escape || dquote || squote))
                { break; }
        }
        #ifdef _LEX_LOOKUP
            _lexer_lookup[_char](lex);
        #else
            switch (_char) {
                case 0x0A:
                    _lexer_newline(lex);
/*
                    ++lex->lineno;
                    if ((current_word) && (!save_reeval)) {
                        if (save_escape && !(dquote || squote)) {
                            --lex->lineno;
                            remove_size_buffer(current_word, 1);
                            if (!_BUFFER_SIZE(current_word))
                                { reeval = true; }
                        } else if (!(dquote || squote))
                            { delim_word = true; }
                    } else
                        { lex->ctoken.ndtype = NEWLINE; }
*/
                    break;

                case ';': case '!': case '&':   
                case '|': case '<': case '>': 
                    _lexer_operator(lex);
                    break;

                #ifdef __GNUC__
                    case '0' ... '9': 
                #else
                    case '0': case '1': case '2': case '3': case '4':
                    case '5': case '6': case '7': case '8': case '9':
                #endif /* __GNUC__ */
                        if (!current_word) {
                            _skip_predicate(&lex->source, &isdigit);
                            if ((*lex->source == '<') || (*lex->source == '>')) {
                                lex->ctoken.ndtype = IO_NUMBER;
                                lex->ctoken.io_num = (size_t)strtol(begin, NULL, 0x0A); 
                                delim_word = true;
                            } else {
                                lex->ctoken.ndtype = _TOKEN;
                                current_word = make_buffer(true);
                                insert_string_size_buffer(current_word,
                                                    begin, (lex->source - begin));
                            }
                        }    
                        break;

                case '#':   _lexer_comment(lex);
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
                                else if ((_char == '`') && (!squote))
                                    { bctick = ~bctick; }
                                else if ((_char == '\\') && (!squote))
                                    { escape = true; }
                            }
            }
        #endif /* _LEX_LOOKUP */
        if (!delim_word)
            { ++lex->source; }

        if ((!current_word) || (delim_word))
            { break; }
        else if ((_char != 0x0A) || (squote || dquote))
            { insert_char_buffer(current_word, _char); }
    }
    if (current_word) { 
        if (_BUFFER_SIZE(current_word))
            { lex->ctoken.lexeme = current_word; }
        else
            { free_buffer(current_word); }
    }
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

#endif 
token_t*
export_token(lexer_t const* lex) {
    if (!lex)
        { return (_TOKEN_NULL); }
    token_t* token = (token_t*)malloc(sizeof(*token));
    if (!token)
        { return (_TOKEN_NULL); }
    (void)memcpy((void*)token, (void*)&lex->ctoken, sizeof(*token));
    if (lex->ctoken.ndtype == _TOKEN) {
        if (!(token->lexeme = copy_buffer(lex->ctoken.lexeme))) {
            free((void*)token);
            return (_TOKEN_NULL);
        }
    }
    return (token);
}
