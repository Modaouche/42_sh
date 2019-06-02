#ifndef _EDITION_H
#define _EDITION_H

#include <stdlib.h>
#include <term.h>
#include "hash.h"
#include "buffer.h"

#define _LINE_NULL              (NULL)
#define _LINE_INPUT(_)          ((buffer_t*)(_)->inpt)
#define _LINE_GET_MODE(_)       ((line_mode_t)(_)->mode)
#define _LINE_SET_MODE(_, _md)  ((_)->mode = _md)
#define _LINE_WIDTH(_)          ((size_t)(_)->widt)
#define _LINE_HEIGHT(_)         ((size_t)(_)->heig)

typedef enum {
    _EMACS  = 0x00,
    _VIM    = 0x01,
} _line_mode_t;

typedef struct {
    buffer_t*       inpt;
    _line_mode_t    mode;
    struct termios  told;
    size_t          widt;
    size_t          heig;
} line_t;

line_t*     set_raw_mode(void);
void        free_line(line_t const*, bool*);
buffer_t*   get_line(line_t*, hash_t const*);

#endif /* _EDITION */
