/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_equal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 22:43:17 by araout            #+#    #+#             */
/*   Updated: 2019/07/12 07:16:02 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char		*get_value(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=' && cmd[i + 1])
			return (&(cmd[i + 1]));
		else if (cmd[i] == '=' && !cmd[i + 1])
			return ("");
		i++;
	}
	return (NULL);
}

char		*get_varname(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
		{
			if (i == 0)
			{
				ft_putstr_fd("Bad assignment\n", 2);
				return (NULL);
			}
			return (ft_strsub(cmd, 0, i));
		}
		i++;
	}
	return (ft_strdup(cmd));
}

int			ft_export_inner_var(char *cmd)
{
	char	*value;

	value = NULL;
	if (!g_shell.intern_var)
		return (0);
	else if (g_shell.intern_var[find_var(cmd, g_shell.intern_var)])
	{
		value = get_env_value(cmd);
		ft_unsetenv(cmd);
		g_shell.envp = set_var_env(cmd, value, g_shell.envp);
	}
	else if (!g_shell.envp[find_var(cmd, g_shell.envp)])
		g_shell.envp = set_var_env(cmd, NULL, g_shell.envp);
	ft_strdel(&value);
	return (1);
}

int			ft_setenv_equal(char *cmd, int flag)
{
	char		*value;
	char		*varname;

	if (!cmd || (!(varname = get_varname(cmd))))
		return (-1);
	value = get_value(cmd);
	if (flag == 1 && value && ft_unsetenv(varname))
		g_shell.envp = set_var_env(varname, value, g_shell.envp);
	else if (flag == 1 && !value)
		ft_export_inner_var(cmd);
	else if (flag == 0 && value)
	{
		if (g_shell.envp[find_var(cmd, g_shell.envp)])
		{
			g_shell.envp = set_var_env(varname, value, g_shell.envp);
			ft_strdel(&varname);
			return (1);
		}
		else
			g_shell.intern_var = set_var_env(varname,\
					value, g_shell.intern_var);
	}
	ft_strdel(&varname);
	return (1);
}
