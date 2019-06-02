#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "edition.h"

line_t*
set_raw_mode(void) {
    static bool _singleton = false;
    if ((_singleton) || (!isatty(STDIN_FILENO)))
        { return (_LINE_NULL); }
    line_t* line = (line_t*)malloc(sizeof(*line));
    if (!line)
        { return (_LINE_NULL); }
    (void)memset((void*)line, 0, sizeof(*line));
    line->inpt = make_buffer(false);
    if (!line->inpt) {
        free((void*)line);
        return (_LINE_NULL);
    }
    if (tcgetattr(STDIN_FILENO, &line->told) == -1) {
        free_line(line, NULL);
        return (_LINE_NULL);
    }
    struct termios new_term = (line->told);
    line->mode = _EMACS;
    new_term.c_lflag &= ~(ECHO | ICANON | ISIG   | IEXTEN);
    new_term.c_iflag &= ~(IXON | ICRNL  | BRKINT | INPCK | ISTRIP);
    new_term.c_oflag &= ~(OPOST);
    new_term.c_lflag |=  (CS8);
    new_term.c_cc[VMIN]  = 0x01;
    new_term.c_cc[VTIME] = 0x00;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_term) == -1) {
        free_line(line, NULL);
        return (_LINE_NULL);
    }
    _singleton = true;
    return (line);
}

void
free_line(line_t const* line, bool* backup_success) {
    if (line) {
        if (backup_success)
            { (*backup_success) = true; }
        if ((tcsetattr(STDIN_FILENO, TCSAFLUSH, &line->told) == -1) && (backup_success))
            { (*backup_success) = false; }
        free_buffer(line->inpt);
        free((void*)line);
    }
}
