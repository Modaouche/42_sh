#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "termcap.h"
#include "utils.h"

static size_t
_strip_useless(char const* str, size_t pos) {
    if ((!str) || (pos && (str[-1] != '\n')))
        { return (0); }
    char const* old_str = str;
    bool in_comment = false;
    while (*str) {
        if (in_comment)         { in_comment = (*str != '\n'); } 
        else if (*str == '#')   { in_comment = true; }
        else if (*str != '\n')  { break; }
        ++str;
    } 
    return (str - old_str);
}

static size_t
_join_line(char const* str, size_t pos) {
    if ((*str != '\\') || (str[1] != '\n'))
        { return (0); }
    char const* old_str = str;
    while ((*str == '\\') && (str[1] == '\n')) {
        str += 0x02;
        while ((*str == ' ') || (*str == '\t'))
            { ++str; }
    }
    return (str - old_str);
}

static size_t
_strip_colons(char const* str, size_t pos) {
    if (*str != ':')
        { return (0); }
    size_t len = 0;
    while (str[len] == ':')
        { ++len; }
    return (len - 1);
}

_Noreturn void
handle_termcap_error(termcap_error_t* terr) {
    
    exit(EXIT_FAILURE);
}

static buffer_t*
_termcap_entry(char const* line, char const* term_name, termcap_error_t* terr) {
    
}

int
_tgetent(buffer_t** bp, char const* name, char const* termcap_env, termcap_error_t* terr) {
    static char const* target_path[] = { "/etc/termcap", NULL };
    if ((!bp) || (!name) || (!terr))
        { return (-1); }
    terr->eof_premature = false;
    buffer_t* tmp_buffer = _BUFFER_NULL;
    buffer_t* target = _BUFFER_NULL;
    bool data_found = false;
    for (size_t i = 0; target_path[i]; ++i) {
        int fd = open(target_path[i], O_RDONLY);
        if (fd != -1) {
            data_found = true;
            if ((tmp_buffer = read_filde(fd, false))) {
                size_t combine_line;
                if (!remove_match_buffer(tmp_buffer, (_match_t)&_join_line, &combine_line)) {
                    /* TODO */
                }
                _BUFFER_SET_CURSOR(tmp_buffer, _BUFFER_SIZE(tmp_buffer));
                _BUFFER_INSERT_CHAR(tmp_buffer, '\n');
                char const* found = _BUFFER_STRING(tmp_buffer);
                do {

                } while ();
                while ((found = (strstr(found, name)))) {
                    if (!(found != _BUFFER_STRING(tmp_buffer)
                                    && ((found[-1] != '|') && (found[-1] != '\n')))) {
                        size_t len = strlen(name);
                        if ((found[len] == '|') || (found[len] == ':')) {
                            size_t len_target = (strchr(found, '\n') - found);
                            target = export_sub_buffer(tmp_buffer,
                                            found - _BUFFER_STRING(tmp_buffer), len_target);
                            _BUFFER_SET_CURSOR(target, _BUFFER_SIZE(target));
                            _BUFFER_INSERT_CHAR(target, ':');
                            remove_match_buffer(target, (_match_t)&_strip_colons);
                            break;
                        } else if (!found[len]) {
                            terr->eof_premature = false;
                            return (-1);
                        }
                    }
                    found += strlen(name);
                }
            } else { /* TODO */ }
            close(fd);
            break;
        }
    }
    (*bp) = target;
    return (1);
}
