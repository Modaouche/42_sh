/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_function.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 06:00:02 by araout            #+#    #+#             */
/*   Updated: 2019/09/23 12:43:44 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void		cd_set_env(int exec_flag, char *pwd)
{
	char	*tmp;

	tmp = NULL;
	if (exec_flag == 1)
	{
		g_shell.envp = set_var_env("OLDPWD", pwd, g_shell.envp);
		ft_strdel(&pwd);
		pwd = getcwd(tmp, 1024);
		g_shell.envp = set_var_env("PWD", pwd, g_shell.envp);
	}
	ft_strdel(&pwd);
}

int			print_env(char **args)
{
	int		i;

	(void)args;
	i = -1;
	while (g_shell.intern_var && g_shell.intern_var[++i])
		ft_printf("%s\n", g_shell.intern_var[i]);
	i = -1;
	while (g_shell.envp[++i])
		ft_printf("%s\n", g_shell.envp[i]);
	return (0);
}

int			ft_clear(char **ptr)
{
	(void)ptr;
	tputs(tgetstr("cl", NULL), 1, ft_puti);
	return (0);
}

int			ft_pwd(char **ptr)
{
	char	*str;

	str = NULL;
	(void)ptr;
	str = getcwd(str, 1024);
	ft_printf("%s\n", str);
	ft_strdel(&str);
	return (0);
}
