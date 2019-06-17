#include "env.h"
/*
**	level_sh incremente le SHLEVEL
*/
void		level_sh(char ***env)
{
	int i;
	int c;
	char *tmp;
	c = 0;
	i = 0;
	while (*env && *env[i])
	{
		if (ft_strnstr(env[i], "SHLVL", ft_cfind(env[i], '='))))//mieu checker la condition
		{
			tmp = *env[i];
			*env[i] = ft_strjoin_free("SHLVL=", ft_itoa(ft_atoi(*env[i] + ft_cfind(env[i], '=')) + 1), 2);
			break ;
		}
		i++;
	}
}
/*
**	env_cpy copie l'environement du shell sur lequlle on se trouve
*/
char 		**env_cpy(char **env)
{
	char **env_c;
	int i;
	
	if (!env)
		return ((char **)ft_memalloc(sizeof(char *)));
	i = 0;
	if (!(env_c = (char **)ft_memalloc(sizeof(char *) * ft_tablen(env) + 1)))
		return (NULL);
	while (env[i])
		env_c[i] = ft_strdup(env[i++]);
	return (env_c);
}