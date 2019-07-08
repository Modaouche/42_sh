/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 07:03:17 by araout            #+#    #+#             */
/*   Updated: 2019/07/08 04:20:59 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int		ft_cd_home(void)
{
	int		index;
	int		exec_flag;

	exec_flag = 0;
	index = find_var("HOME", g_shell.envp);
	if (g_shell.envp[index])
	{
		exec_flag = check_perms(g_shell.envp[index] + 5);
		if (exec_flag == -2)
		{
			if (access(g_shell.envp[index] + 5, X_OK))
				exec_flag = -3;
			else
				exec_flag = 1;
		}
		else if (exec_flag == -1)
			exec_flag = -4;
		else if (exec_flag == 0)
			exec_flag = -5;
		throw_error(g_shell.envp[index] + 5, exec_flag);
		chdir(g_shell.envp[index] + 5);
	}
	return (exec_flag);
}

static void		cd_set_env(int exec_flag, char *pwd)
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

static int		ft_cd_minest(void)
{
	return (1);
}

int				ft_cd(char **cmd)
{
	int		exec_flag;
	char	*pwd;

	(void)cmd;
	pwd = getcwd(NULL, 1024);
	exec_flag = 0;
	if (!cmd[1])
		exec_flag = ft_cd_home();
	else if (!ft_strcmp(cmd[1], "-"))
		exec_flag = ft_cd_minest();
	cd_set_env(exec_flag, pwd);
	return (1);
}
