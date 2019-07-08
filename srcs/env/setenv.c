/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 07:21:17 by araout            #+#    #+#             */
/*   Updated: 2019/07/08 08:18:49 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void			free_env(void)
{
	int		i;

	i = 0;
	while (g_shell.envp[i])
		free(g_shell.envp[i++]);
	free(g_shell.envp);
}

int				ft_setenv(char **cmd)
{
	if (!cmd || !cmd[1] || !cmd[2])
	{
		ft_putstr_fd("setenv error: 2 argument required\n", 2);
		return (0);
	}
	else if (cmd[3])
	{
		ft_putstr_fd("setenv error: Takes only 2 arguments\n", 2);
		return (0);
	}
	if (!g_shell.envp)
		g_shell.envp = set_var_env(cmd[1], cmd[2], NULL);
	else
	{
		g_shell.envp = set_var_env(cmd[1], cmd[2], g_shell.envp);
	}
	return (1);
}

static char		**dump_env_unset(int index)
{
	int		size;
	char	**new;
	int		i;
	int		j;

	size = 0;
	while (g_shell.envp[size])
		size++;
	if (!(new = (char **)ft_memalloc((sizeof(new) * (size)))))
		return (NULL);
	new[size - 1] = NULL;
	i = -1;
	j = 0;
	while (g_shell.envp[++i] != NULL)
	{
		if (i != index)
		{
			new[j] = ft_strdup(g_shell.envp[i]);
			j++;
		}
		ft_strdel(&(g_shell.envp[i]));
	}
	free(g_shell.envp);
	return (new);
}

int				ft_unsetenv(char **cmd)
{
	int		index;

	if (!cmd || !*cmd || !cmd[1])
	{
		ft_printf("unsetenv error: Take 1 argument\n");
		return (0);
	}
	index = find_var(cmd[1], g_shell.envp);
	if (g_shell.envp && g_shell.envp[index])
		g_shell.envp = dump_env_unset(index);
	else
		ft_putstr_fd("Unsetenv error : Cannot find Variable\n", 2);
	return (0);
}
