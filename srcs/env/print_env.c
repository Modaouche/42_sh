#include "env.h"

void        print_env(char **env)
{
    int c;
    if (env)
    {
        c = 0;
        while (env[c])
            ft_putendl(env[c++]);
    }
}