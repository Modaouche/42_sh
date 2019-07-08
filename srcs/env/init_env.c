/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 23:04:21 by araout            #+#    #+#             */
/*   Updated: 2019/07/08 03:59:51 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char			*sh_lvl(char **env)
{
	int		shlvl;
	int		index;

	index = find_var("SHLVL", env);
	if (env && env[index])
	{
		shlvl = ft_atoi(&env[index][6]) + 1;
		return (ft_itoa(shlvl));
	}
	else
		return (ft_strdup("1"));
}

char			**get_env(char **env)
{
	int		i;
	char	**newenv;

	i = 0;
	if (env && *env)
	{
		while (env[i])
			i++;
		if (!(newenv = (char **)ft_memalloc(sizeof(char **) * (i + 1) + 1)))
			return (NULL);
		newenv[i] = NULL;
		i = -1;
		while (env[++i])
			newenv[i] = ft_strdup(env[i]);
	}
	else
	{
		return (NULL);
	}
	return (newenv);
}

void			init_env(char **env)
{
	char *tmp;

	if (!(g_shell.envp = get_env(env)))
		return ;
	tmp = sh_lvl(env);
	if ((g_shell.envp = set_var_env("SHLVL", tmp, g_shell.envp)) == NULL)
	{
		free(tmp);
		return ;
	}
	free(tmp);
}
