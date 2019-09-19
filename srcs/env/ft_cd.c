/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 07:03:17 by araout            #+#    #+#             */
/*   Updated: 2019/07/09 22:07:31 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int		ft_cd_home(void)
{
	int		index;
	int		exec_flag;

	exec_flag = 0;
	index = find_var_idx("HOME", g_shell.envp);
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

static int		ft_cd_absolute(char *path)
{
	int		exec_flag;

	exec_flag = check_perms(path);
	if (exec_flag == -2)
	{
		if (access(path, X_OK))
			exec_flag = -3;
		else
			exec_flag = 1;
	}
	else if (exec_flag == -1)
		exec_flag = -4;
	else if (exec_flag == 0)
		exec_flag = -5;
	throw_error(path, exec_flag);
	chdir(path);
	return (exec_flag);
}

static int		ft_cd_relative(char *path)
{
	int			exec_flag;
	char		*absolute_path;
	char		*tmp;
	char		*tmp2;

	if (!path)
		return (-11);
	tmp = NULL;
	tmp = getcwd(tmp, 1024);
	if (ft_strcmp("/", tmp))
	{
		tmp2 = tmp;
		tmp = ft_strjoin(tmp, "/");
		ft_strdel(&tmp2);
	}
	absolute_path = ft_strjoin(tmp, path);
	ft_strdel(&tmp);
	exec_flag = ft_cd_absolute(absolute_path);
	ft_strdel(&absolute_path);
	return (exec_flag);
}

static int		ft_cd_minest(void)
{
	int		index;
	char	*tmp;

	tmp = NULL;
	index = find_var_idx("OLDPWD", g_shell.envp);
	if (g_shell.envp[index])
		tmp = ft_strdup(g_shell.envp[index] + 7);
	else
	{
		index = find_var_idx("HOME", g_shell.envp);
		if (g_shell.envp[index])
			tmp = ft_strdup(g_shell.envp[index] + 5);
	}
	index = ft_cd_absolute(tmp);
	ft_strdel(&tmp);
	return (index);
}

int				ft_cd(void *ptr)
{
	int		exec_flag;
	char	*pwd;
	char	**cmd;

	cmd = ptr;
	if (!cmd || !*cmd)
		return (-1);
	pwd = getcwd(NULL, 1024);
	exec_flag = 0;
	if (!cmd[1])
		exec_flag = ft_cd_home();
	else if (!ft_strcmp(cmd[1], "-"))
		exec_flag = ft_cd_minest();
	else if (cmd[1][0] == '/')
		exec_flag = ft_cd_absolute(cmd[1]);
	else if (cmd[1][0] != '/')
		exec_flag = ft_cd_relative(cmd[1]);
	cd_set_env(exec_flag, pwd);
	return (exec_flag);
}
