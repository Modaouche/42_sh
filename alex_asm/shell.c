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
    lexer->lconti = make_list(NULL, NULL);
    if (!lexer->lconti) {
        free_lexer(lexer);
        return (_LEXER_NULL);
    }
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
free_lexer(lexer_t const* lexer) {
    if (lexer) {
        if (lexer->ctoken.ndtype == _TOKEN)
            { free_buffer(lexer->ctoken.lexeme); }
        free_list(lexer->lconti);
        free_buffer(lexer->source);
        free((void*)lexer);
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
_lexer_operator(lexer_t* lexer) {
    char register char_1 = _BUFFER_CURSOR_CHAR(lexer->source);
    char register char_2 = _BUFFER_CURSOR_STRING(lexer->source)[1];
    switch (char_1) {
        case ';':
        case '!':   lexer->ctoken.ndtype = char_1;
                    break;
        case '&':   lexer->ctoken.ndtype = '&';
                    if (char_2 == '&') {
                        lexer->ctoken.ndtype = AND_IF;
                        _BUFFER_FORWARD_CURSOR(lexer->source);
                    }
                    break;

        case '|':   lexer->ctoken.ndtype = '|';
                    if (char_2 == '|') {
                        lexer->ctoken.ndtype = OR_IF;
                        _BUFFER_FORWARD_CURSOR(lexer->source);
                    }
                    break;

        case '<':   lexer->ctoken.ndtype = '<';
                    _BUFFER_FORWARD_CURSOR(lexer->source);
                    switch (char_2) {
                        case '&':   lexer->ctoken.ndtype = LESSAND; break;
                        case '<':   lexer->ctoken.ndtype = DLESS; break;
                        case '>':   lexer->ctoken.ndtype = LESSGREAT;
                            if (_BUFFER_CURSOR_STRING(lexer->source)[1] == '-') {
                                lexer->ctoken.ndtype = DLESSDASH;
                                _BUFFER_FORWARD_CURSOR(lexer->source);
                            }
                            break;
                        default:    _BUFFER_REVERSE_CURSOR(lexer->source);
                    }
                    break;

        case '>':   lexer->ctoken.ndtype = '>';
                    _BUFFER_FORWARD_CURSOR(lexer->source);
                    switch (char_2) {
                        case '&':   lexer->ctoken.ndtype = GREATAND; break;
                        case '>':   lexer->ctoken.ndtype = DGREAT; break;
                        case '|':   lexer->ctoken.ndtype = CLOBBER; break;
                        default:    _BUFFER_REVERSE_CURSOR(lexer->source); 
                    } 
                    break;
    }
    _BUFFER_FORWARD_CURSOR(lexer->source);
}

static void
_lexer_newline(lexer_t* lexer) {
    _BUFFER_FORWARD_CURSOR(lexer->source);
    lexer->ctoken.ndtype = NEWLINE;
    ++(lexer->lineno);
}

static void
_lexer_comment(lexer_t* lexer) {
    _skip_predicate(lexer->source, &_is_not_newline);
}

static bool
_lexer_token_squote(lexer_t* lexer) {
    if (_BUFFER_CURSOR_CHAR(lexer->source) == '\'') {
        _LIST_PUSH_BACK(lexer->lconti, (void*)UNBALANCE_SQUOTE);
        _BUFFER_FORWARD_CURSOR(lexer->source);
    }
    while ((!_BUFFER_EOF(lexer->source)) && (_BUFFER_CURSOR_CHAR(lexer->source) != '\''))
        { _BUFFER_FORWARD_CURSOR(lexer->source); }
    if (!_BUFFER_EOF(lexer->source))    { _LIST_POP_BACK(lexer->lconti); }
    else                                { return (false); }
    return (true);
}

static bool
_lexer_token_bquote(lexer_t* lexer) {
    if (_BUFFER_CURSOR_CHAR(lexer->source) == '`') {
        _LIST_PUSH_BACK(lexer->lconti, (void*)UNBALANCE_BQUOTE);
        _BUFFER_FORWARD_CURSOR(lexer->source);
    }
    bool escape = false;
    while (!_BUFFER_EOF(lexer->source)) {
        if (escape)
            { escape = false; }
        else {
            if (_BUFFER_CURSOR_CHAR(lexer->source) == '`')
                { break; }
            else if (_BUFFER_CURSOR_CHAR(lexer->source) == '\\')
                { escape = true; }
        }
        _BUFFER_FORWARD_CURSOR(lexer->source);
    }
    if (!_BUFFER_EOF(lexer->source))    { _LIST_POP_BACK(lexer->lconti); }
    else                                { return (false); }
    return (true);
}

static int
_is_identifier(char c) {
    return ((isalnum(c)) || (c == '_'));
}

static bool _lexer_token_dquote(lexer_t*, size_t);

#define _DEPTH_START    (0x00)
#define _DEPTH_LIMIT    (0xFF)

static bool
_lexer_token_dollar(lexer_t* lexer, size_t depth, ...) {
    if (depth > (_DEPTH_LIMIT - _DEPTH_START)) {
        lexer->edepth = true;
        return (true);
    }
    bool param_expand = false;
    bool command_subs = false;
    bool arith_expand = false;
    bool regex_expand = false;

    bool escape = false;
    bool braces = false;
    if (_BUFFER_CURSOR_CHAR(lexer->source) == '$') {
        _BUFFER_FORWARD_CURSOR(lexer->source);
        if (_BUFFER_CURSOR_CHAR(lexer->source) == '(') {
            _BUFFER_FORWARD_CURSOR(lexer->source);
            if (_BUFFER_CURSOR_STRING(lexer->source)[1] == '(') { 
                arith_expand = true;
            } else { 
                _BUFFER_REVERSE_CURSOR(lexer->source);
                command_subs = true;
            }
        } else {
            if (_BUFFER_CURSOR_CHAR(lexer->source) == '[') {
                _BUFFER_FORWARD_CURSOR(lexer->source);
                regex_expand = true;
            } else {
                param_expand = true;
                if (_BUFFER_CURSOR_CHAR(lexer->source) == '{') {
                    _BUFFER_FORWARD_CURSOR(lexer->source);
                    braces = true;
                }
            }
        }
        if (param_expand)       { _LIST_PUSH_BACK(lexer->lconti, (void*)UNBALANCE_DPARAM); }
        else if (command_subs)  { _LIST_PUSH_BACK(lexer->lconti, (void*)UNBALANCE_DCOMDS); }
        else if (arith_expand)  { _LIST_PUSH_BACK(lexer->lconti, (void*)UNBALANCE_DARITH); }
        else if (regex_expand)  { _LIST_PUSH_BACK(lexer->lconti, (void*)UNBALANCE_DREGEX); }
    } else {
        va_list list;
        va_start(list, depth);
        switch (va_arg(list, int)) {
            case UNBALANCE_DPARAM:  param_expand = true; break;
            case UNBALANCE_DCOMDS:  command_subs = true; break;
            case UNBALANCE_DARITH:  arith_expand = true; break;
            case UNBALANCE_DREGEX:  regex_expand = true; break;
        }
        va_end(list);
    }

    while (!_BUFFER_EOF(lexer->source)) {
        if ((param_expand) && (!braces)) {
            if (!_is_identifier(_BUFFER_CURSOR_CHAR(lexer->source))) {
                _BUFFER_REVERSE_CURSOR(lexer->source);
                return (true);
            }
        }
        if (escape)
            { escape = false; }
        else {
            char register _char = _BUFFER_CURSOR_CHAR(lexer->source);
            if ((param_expand) && (_char == '}'))
                { break; }
            else if ((regex_expand) && (_char == ']'))
                { break; }
            else if ((!param_expand) && (_char ==  ')')) {
                if (command_subs)
                    { break; }
                else if (_BUFFER_CURSOR_STRING(lexer->source)[1] == ')') {
                    _BUFFER_FORWARD_CURSOR(lexer->source);
                    break;
                }
            }
            else {
                switch (_char) {
                    case '\\':  escape = true; break;
                    case '\'':  (void)_lexer_token_squote(lexer); break;
                    case '`':   (void)_lexer_token_bquote(lexer); break;
                    case '"':   (void)_lexer_token_dquote(lexer, depth + 1); break;
                    case '$':   if ((!regex_expand)
                                    || (_BUFFER_CURSOR_STRING(lexer->source)[1] == ']'))
                                        { (void)_lexer_token_dollar(lexer, depth + 1); }
                                    break;
                }
            }
        }
        _BUFFER_FORWARD_CURSOR(lexer->source);
    }
    if (!_BUFFER_EOF(lexer->source))    { _LIST_POP_BACK(lexer->lconti); }
    else                                { return (false); }
    return (true);
}

static bool
_lexer_token_dquote(lexer_t* lexer, size_t depth) {
    if (depth > (_DEPTH_LIMIT - _DEPTH_START)) {
        lexer->edepth = true;
        return (true);
    } else if (_BUFFER_CURSOR_CHAR(lexer->source) == '"') {
        _LIST_PUSH_BACK(lexer->lconti, (void*)UNBALANCE_DQUOTE);
        _BUFFER_FORWARD_CURSOR(lexer->source);
    }
    bool escape = false;
    while (!_BUFFER_EOF(lexer->source)) {
        if (escape)
            { escape = false; }
        else {
            if (_BUFFER_CURSOR_CHAR(lexer->source) == '"')
                { break; }
            switch (_BUFFER_CURSOR_CHAR(lexer->source)) {
                case '\\':  escape = true; break;
                case '`':   (void)_lexer_token_bquote(lexer); break;
                case '$':   (void)_lexer_token_dollar(lexer, depth + 1); break;
            }
        } 
        _BUFFER_FORWARD_CURSOR(lexer->source);
    }
    if (!_BUFFER_EOF(lexer->source))    { _LIST_POP_BACK(lexer->lconti); }
    else                                { return (false); }
    return (true);
}

#define _TOKEN_NFIRST           "\n;!&|<>#"
#define _IS_WORD(_)             ((!isblank(_)) && (!strchr(_TOKEN_NFIRST, (_))))

static void
_lexer_token(lexer_t* lexer) {
    lexer->ctoken.ndtype = _CONTINUE;
    buffer_t* current_word = make_buffer(true);
    if (!current_word)
        { return; }
    bool escape = false;
    bool finish = true;
    while ((!_BUFFER_EOF(lexer->source))
                            && (_IS_WORD(_BUFFER_CURSOR_CHAR(lexer->source)) || (escape))) {
        bool _write = true;
        if (escape) {
            if (_BUFFER_CURSOR_CHAR(lexer->source) == 0x0A) {
                remove_size_buffer(current_word, 1);
                _write = false;
            }
            escape = false;
        } else {
            size_t begin = _BUFFER_GET_CURSOR(lexer->source);
            switch (_BUFFER_CURSOR_CHAR(lexer->source)) {
                case '\\':  escape = true; break;
                case '\'':  finish = _lexer_token_squote(lexer); break;
                case '`':   finish = _lexer_token_bquote(lexer); break;
                case '"':   finish = _lexer_token_dquote(lexer, _DEPTH_START); break;
                case '$':   finish = _lexer_token_dollar(lexer, _DEPTH_START); break;
            }
            size_t end = _BUFFER_GET_CURSOR(lexer->source);
            insert_string_size_buffer(current_word,
                        &_BUFFER_CURSOR_STRING(lexer->source)[begin - end], end - begin);
        }
        if (_write)
            { _BUFFER_INSERT_CHAR(current_word, _BUFFER_CURSOR_CHAR(lexer->source)); }
        _BUFFER_FORWARD_CURSOR(lexer->source);
    }
    if (_BUFFER_SIZE(current_word)) {
        if ((finish) && (!escape)) {
            _BUFFER_SET_CURSOR(current_word, 0);
            lexer->ctoken.ndtype = _TOKEN;
        } else if (escape) {
            _LIST_PUSH_BACK(lexer->lconti, (void*)UNBALANCE_EDLINE);
            remove_size_buffer(current_word, 1);
        }
        if (!lexer->ctoken.lexeme)  { lexer->ctoken.lexeme = current_word; }
        else                        { _BUFFER_APPEND(lexer->ctoken.lexeme, current_word); }
    } else { 
        lexer->ctoken.ndtype = _NONE;
        free_buffer(current_word);
    }
}

static void
_lexer_io_number(lexer_t* lexer) {
    if (!isdigit(_BUFFER_CURSOR_CHAR(lexer->source)))
        { return; }
    size_t begin = _BUFFER_GET_CURSOR(lexer->source);
    _skip_predicate(lexer->source, &isdigit);
    switch (_BUFFER_CURSOR_CHAR(lexer->source)) {
        case '<':
        case '>':
            /* TODO CHECK OVERFLOW */
            lexer->ctoken.ndtype = IO_NUMBER;
            lexer->ctoken.io_num = (size_t)strtol(_BUFFER_STRING(lexer->source) + begin,
                                                NULL, 0x0A); 
            break;
        default:
            _BUFFER_SET_CURSOR(lexer->source, begin);
            _lexer_token(lexer);
    }
}

//#ifdef _LEX_LOOKUP

static _tokenset_t
_lexer_lookup[UCHAR_MAX + 0x01] = {
//    #ifndef __GNUC__
        /* 0x00 - 0x09 */   &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token,
        /* 0x0A */          &_lexer_newline,
        /* 0x0B - 0x20 */   &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token,
        /* 0x21 */          &_lexer_operator, 
        /* 0x22 */          &_lexer_token,
        /* 0x23 */          &_lexer_comment,
        /* 0x24 - 0x25 */   &_lexer_token,
        /* 0x26 */          &_lexer_operator,
        /* 0x27 - 0x2F */   &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
        /* 0x30 - 0x39 */   &_lexer_io_number, &_lexer_io_number, &_lexer_io_number,
                            &_lexer_io_number, &_lexer_io_number, &_lexer_io_number,
                            &_lexer_io_number, &_lexer_io_number, &_lexer_io_number,
                            &_lexer_io_number,
        /* 0x3A */          &_lexer_token,
        /* 0x3B */          &_lexer_operator,
        /* 0x3C */          &_lexer_operator,
        /* 0x3D */          &_lexer_token,
        /* 0x3E */          &_lexer_operator,
        /* 0x3F - 0x7B */   &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
        /* 0x7C */          &_lexer_operator,
        /* 0x7D - 0xFF */   &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token, &_lexer_token,
                            &_lexer_token, &_lexer_token, &_lexer_token,

//    #else
/*
        [0x00 ... 0x09]     = &_lexer_token,
        [0x0A]              = &_lexer_newline,
        [0x0B ... 0x20]     = &_lexer_token,
        [0x21]              = &_lexer_operator, 
        [0x22]              = &_lexer_token,
        [0x23]              = &_lexer_comment,
        [0x24 ... 0x25]     = &_lexer_token,
        [0x26]              = &_lexer_operator,
        [0x27 ... 0x2F]     = &_lexer_token,
        [0x30 ... 0x39]     = &_lexer_io_number,
        [0x3A]              = &_lexer_token,
        [0x3B]              = &_lexer_operator,
        [0x3C]              = &_lexer_operator,
        [0x3D]              = &_lexer_token,
        [0x3E]              = &_lexer_operator,
        [0x3F ... 0x7B]     = &_lexer_token,
        [0x7C]              = &_lexer_operator,
        [0x7D ... 0xFF]     = &_lexer_token,
*/
//    #endif /* __GNUC__ */
};

//#endif /* _LEX_LOOKUP */

token_type_t
next_token_lexer(lexer_t* lexer) {
    if (!lexer)
        { return (_ERROR); }
    if (_LIST_SIZE(lexer->lconti)) {
        iter_list_t iter;
        init_iter_list(lexer->lconti, &iter, REVERSE);
        element_t* element;
        bool _continue = true;
        while ((_continue) && (element = next_iter_list(&iter))) {
            _continue = false;
            switch ((_error_token_t)*element) {
                case UNBALANCE_EDLINE:  _lexer_token(lexer); break;
                case UNBALANCE_SQUOTE:  _continue = _lexer_token_squote(lexer); break;
                case UNBALANCE_BQUOTE:  _continue = _lexer_token_bquote(lexer); break;
                case UNBALANCE_DQUOTE:  _continue = _lexer_token_dquote(lexer, _DEPTH_START);
                                        break;
                case UNBALANCE_DPARAM:
                case UNBALANCE_DCOMDS:
                case UNBALANCE_DARITH:
                case UNBALANCE_DREGEX:
                        _continue = _lexer_token_dollar(lexer, (_error_token_t)*element);
                        break;
            }
            if (_continue)
                { _LIST_POP_BACK(lexer->lconti); }
        }
        if (_continue)
            { lexer->ctoken.ndtype = _TOKEN; }
    } else {
        if (lexer->ctoken.ndtype == _TOKEN)
            { free_buffer(lexer->ctoken.lexeme); }
        lexer->ctoken.ndtype = _NONE;
        lexer->ctoken.lexeme = NULL;
        lexer->edepth = false;
        while (lexer->ctoken.ndtype == _NONE) {
            _skip_predicate(lexer->source, &isblank);
            if (_BUFFER_EOF(lexer->source)) {
                lexer->ctoken.ndtype = _EOF;
                break;
            }
            char register _char = _BUFFER_CURSOR_CHAR(lexer->source);
            #ifdef _LEX_LOOKUP
                _lexer_lookup[_char](lexer);
            #else
                switch (_char) {
                    case 0x0A:  _lexer_newline(lexer);      break;
                    case ';': case '!': case '&':
                    case '|': case '<': case '>':
                                _lexer_operator(lexer);     break;

                    #ifdef __GNUC__
                        case '0' ... '9': 
                    #else
                        case '0': case '1': case '2': case '3': case '4':
                        case '5': case '6': case '7': case '8': case '9':
                    #endif /* __GNUC__ */
                                _lexer_io_number(lexer);    break;

                    case '#':   _lexer_comment(lexer);      break;
                    default:    _lexer_token(lexer);
                }
            #endif /* _LEX_LOOKUP */
        }
    }
    return (lexer->ctoken.ndtype);
}

#if 0

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
