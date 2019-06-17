#include "env.h"
/*
** Remove value env
*/
void		ft_remove_place_env(char ***env, char *to_remove)
{
	int i;
	int c;
	int k;
	char **new_tab;

	i = -1;
	if ((c = check_env_value(*env, to_remove))
	{
		k = 0;
		if (!(new_tab = (char **)ft_memalloc(sizeof(char *) * ft_tablen + 1)))
			return ;
		while (*env[++i])
		{
			if (i == c)
				continue ;
			new_tab[k++] = ft_strdup(*env[i]);		
		}
		new_tab[k] = 0;
		ft_free_tab(*env);
		*env = new_tab;
	}
}