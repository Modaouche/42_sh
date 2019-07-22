/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 06:10:51 by araout            #+#    #+#             */
/*   Updated: 2019/07/15 01:22:35 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char			*get_env_value(char *varname)
{
	int		vpos;

	vpos = find_var(varname, g_shell.intern_var);
	if (g_shell.envp && g_shell.envp[find_var(varname, g_shell.envp)])
		return (ft_strdup(g_shell.envp[find_var(varname, g_shell.envp)]\
					+ ft_strlen(varname) + 1));
	else if (g_shell.intern_var && g_shell.intern_var[find_var(varname,\
				g_shell.intern_var)])
		return (ft_strdup((g_shell.intern_var[vpos]) + ft_strlen(varname) + 1));
	return (NULL);
}

int				is_var(char *s1, char *s2)
{
	int		i;

	i = 0;
	s2 = ft_strjoin(s2, "=");
	while (s1[i] == s2[i] && s1[i] != '=' && s2[i] != '=')
		i++;
	if (s1[i] == s2[i])
	{
		ft_strdel(&s2);
		return (1);
	}
	ft_strdel(&s2);
	return (0);
}

char			**set_var_env(char *varname, char *value, char **env)
{
	char		*tmp;
	int			index;

	index = find_var(varname, env);
	if (!(tmp = ft_strjoin(varname, "=")))
		return (NULL);
	if (env && env[index])
	{
		ft_strdel(&(env[index]));
		if (!value)
			env[index] = tmp;
		else if ((env[index] = ft_strjoin(tmp, value)) || 1)
			ft_strdel(&tmp);
	}
	else
	{
		env = dump_env(env, index + 1);
		if (!value)
			env[index] = tmp;
		else if ((env[index] = ft_strjoin(tmp, value)) || 1)
			ft_strdel(&tmp);
	}
	return (env);
}

int				find_var(char *varname, char **env)
{
	int		i;

	i = 0;
	if (!env || !env[i])
		return (i);
	while (env && env[i] && !is_var(env[i], varname))
		i++;
	return (i);
}

char			**dump_env(char **env, int size)
{
	int		i;
	char	**new;

	if (env == NULL)
	{
		if (!(new = (char **)ft_memalloc(sizeof(new) * 2)))
			return (NULL);
		return (new);
	}
	if (!(new = (char **)ft_memalloc(sizeof(new) * (size + 1))))
		return (NULL);
	new[size] = NULL;
	i = -1;
	while (env && env[++i])
	{
		new[i] = ft_strdup(env[i]);
		ft_strdel(&env[i]);
	}
	if (env)
		ft_memdel((void *)&env);
	return (new);
}
