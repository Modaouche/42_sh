#ifndef ENV_H
#define ENV_H
#include "../libft/libft.h"

/*
**  Init env
*/
char 		**create_env_loc(char **env);
char 		**env_cpy(char **env);
/*
**  Routine env
*/
int			check_env_value(char **env, char *to_check);
/*
**  Change env value
*/
void		ft_remove_place_env(char ***env, char *to_remove);
void		ft_add_place_env(char ***env, char *new_var);
/*
** Print env  
*/
void        print_env(char **env);

#endif