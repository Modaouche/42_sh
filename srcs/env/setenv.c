/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 07:21:17 by araout            #+#    #+#             */
/*   Updated: 2019/07/10 05:00:34 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void			free_env(void)
{
	int		i;

	i = 0;
	while (g_shell.envp && g_shell.envp[i])
		free(g_shell.envp[i++]);
	free(g_shell.envp);
	i = 0;
	while (g_shell.intern_var && g_shell.intern_var[i])
		free(g_shell.intern_var[i++]);
	if (g_shell.intern_var)
		free(g_shell.intern_var);
}

int				ft_setenv(void *ptr)
{
	char	**cmd;

	cmd = ptr;
	if (!cmd || !cmd[1])
	{
		print_env(NULL);
		return (0);
	}
	else if (cmd[0] && cmd[1] && !cmd[2])
		ft_setenv_equal(cmd[1], 1);
	return (1);
}

static char		**dump_env_unset(int index, char **env)
{
	int		size;
	char	**new;
	int		i;
	int		j;

	size = 0;
	while (env[size])
		size++;
	if (!(new = (char **)ft_memalloc((sizeof(new) * (size)))))
		return (NULL);
	new[size - 1] = NULL;
	i = -1;
	j = 0;
	while (env[++i] != NULL)
	{
		if (i != index)
		{
			new[j] = ft_strdup(env[i]);
			j++;
		}
		ft_strdel(&(env[i]));
	}
	free(env);
	return (new);
}

int				ft_unsetenv_cmd(void *ptr)
{
	int		index;
	char	**cmd;
	int		index2;

	cmd = ptr;
	if (!cmd || !cmd[0] || !cmd[1])
	{
		ft_printf("unset error: Take 1 argument\n");
		return (0);
	}
	index = find_var_idx(cmd[1], g_shell.envp);
	index2 = find_var_idx(cmd[1], g_shell.intern_var);
	if (g_shell.envp && g_shell.envp[index])
		g_shell.envp = dump_env_unset(index, g_shell.envp);
	else if (g_shell.intern_var && g_shell.intern_var[index2])
		g_shell.intern_var = dump_env_unset(index2, g_shell.intern_var);
	return (1);
}

int				ft_unsetenv(void *ptr)
{
	int		index;
	char	*cmd;
	int		index2;

	cmd = ptr;
	if (!cmd)
	{
		ft_printf("unset error: Take 1 argument\n");
		return (0);
	}
	index = find_var_idx(cmd, g_shell.envp);
	index2 = find_var_idx(cmd, g_shell.intern_var);
	if (g_shell.envp && g_shell.envp[index])
		g_shell.envp = dump_env_unset(index, g_shell.envp);
	else if (g_shell.intern_var && g_shell.intern_var[index2])
		g_shell.intern_var = dump_env_unset(index2, g_shell.intern_var);
	return (1);
}
