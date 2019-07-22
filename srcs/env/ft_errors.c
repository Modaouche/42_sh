/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 07:09:59 by araout            #+#    #+#             */
/*   Updated: 2019/07/08 00:07:25 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int		throw_error2(char *str, int exec_flag)
{
	if (exec_flag == -3)
	{
		ft_putstr_fd("cd: Permission denied: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (exec_flag == -4)
	{
		ft_putstr_fd("cd: not a directory: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (exec_flag == -5)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	return (0);
}

int				throw_error(char *str, int exec_flag)
{
	if (exec_flag == -1)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" : Permission Denied\n", 2);
		return (-1);
	}
	else if (exec_flag == 0)
	{
		ft_putstr_fd("Cannot find : ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (exec_flag == -2)
	{
		ft_putstr_fd("Cannot execute : ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" is a Directory.\n", 2);
	}
	else
		throw_error2(str, exec_flag);
	return (0);
}

int				check_perms(char *path)
{
	struct stat	buf;
	int			flag;
	int			s;

	flag = 0;
	buf.st_mode = 0;
	s = stat(path, &buf);
	if (S_ISREG(buf.st_mode) && !access(path, X_OK))
		flag = 1;
	if (!access(path, F_OK) && access(path, X_OK))
		flag = -1;
	if (S_ISDIR(buf.st_mode))
		flag = -2;
	return (flag);
}
