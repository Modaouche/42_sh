/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 11:43:36 by araout            #+#    #+#             */
/*   Updated: 2019/08/30 12:25:02 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int			check_built_in(char *args)
{
	int		i;
	int		j;
	int		flag;

	i = 0;
	flag = 0;
	j = -1;
	while (g_shell.fptr->flag[++j])
	{
		if (!(ft_strcmp(g_shell.fptr->flag[j], args)))
		{
			ft_printf("%s is a shell builtin\n", args);
			return (1);
		}
	}
	return (0);
}

int			check_path_var(char *args)
{
	char	*path;
	char	**split_path;
	int		i;
	char	*tmp;

	i = -1;
	path = get_env_value("PATH");
	split_path = ft_split(path, ":");
	while (split_path[++i])
	{
		tmp = ft_strjoin(split_path[i], "/");
		ft_strdel(&path);
		path = ft_strjoin(tmp, args);
		ft_strdel(&tmp);
		if (!access(path, X_OK))
		{
			ft_printf("%s is %s\n", args, path);
			ft_strdel(&path);
			free_tmp(split_path);
			return (1);
		}
		ft_strdel(&path);
	}
	free_tmp(split_path);
	return (0);
}

int			type_main(void *ptr)
{
	char	**args;
	int		i;
	int		flag;

	flag = 0;
	args = ptr;
	i = 0;
	if (!args || !args[0] || !args[1])
		return (-1);
	while (args[++i])
	{
		if (check_built_in(args[i]))
			flag = 1;
		else if (check_path_var(args[i]))
			flag = 1;
		if (!flag)
			ft_printf("%s not found\n", args[i]);
	}
	return (flag);
}
