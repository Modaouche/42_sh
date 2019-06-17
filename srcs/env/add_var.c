#include "env.h"
/*
**	ft_add_place_env ajoute une nouvelle variable a l'env
*/
void		ft_add_place_env(char ***env, char *new_var)
{
	char **new_env;
	int c;

	c = 0;
	if (!(new_env = (char **)ft_memalloc(sizeof(char *) * ft_tablen(*env) + 1)))
		return (NULL);
	while (*env && *env[c])
	{
		new_env[c] = ft_strdup(*env[c]);
		c++;
	}
	ft_free_tab(*env);
	new_env[c++] = ft_strdup(new_var);
	new_env[c] = 0;
	*env = new_env;
}