#include "env.h"
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
	if (!(env_c = (char **)ft_memalloc(sizeof(char *) * (ft_tablen(env) + 1))))
		return (NULL);
	while (env[i])
	{
		if (ft_strnstr(env[i], "SHLVL", ft_cfind(env[i], '=')))
			env_c[i] = ft_strjoin("SHLVL=", ft_itoa(1 + ft_atoi(env[i] + ft_cfind(env[i], '=') + 1)));
		else
			env_c[i] = ft_strdup(env[i]);
		i++;
	}
	env_c[i] = NULL;
	return (env_c);
}