#ifndef _TERMCAP_H
#define _TERMCAP_H

#include "buffer.h"

typedef struct {
    bool    eof_premature;
    size_t  line;
    size_t  column;
} termcap_error_t;

_Noreturn void  handle_termcap_error(termcap_error_t*);
int             _tgetent(buffer_t**, char const*, char const*, termcap_error_t*);

#endif /* _TERMCAP_H */
