#ifndef _HISTORY_H
#define _HISTORY_H

#include <stdbool.h>
#include "list.h"

typedef struct {
    list_t* csaved;
    bool    enable;
}

#endif /* _HISTORY_H */
