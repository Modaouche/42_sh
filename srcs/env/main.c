

int			check_env_value(char **env, char *to_check)
{
	int c;

	if (env)
	{
		c = 0;
		while (env[c])
		{
			if (ft_strnstr(env[i], to_check, ft_cfind(env[i], '='))
				return (c);
			c++;
		}
	}
	return (0);
}

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
		if (!(new_tab = (char **)ft_memalloc(sizeof(char *) * ft_tablen)))
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
	if (!(env_c = (char **)ft_memalloc(sizeof(char *) * ft_tablen(env))))
		return (NULL);
	while (env[i])
		env_c[i] = ft_strdup(env[i++]);
	return (env_c);
}

int		manag_env(char **env, char **arg)
{
	char **env_sh;
	int flag;

	env_sh = env_cpy(env);
	sh_level(&env);
	if (FLAG_U & flag)
		ft_remove(env_sh, )	
	return (1);// return (exit success)
}


int main(int ac, char **av, char **env)
{
	manag_env(env);
	return (0);
}