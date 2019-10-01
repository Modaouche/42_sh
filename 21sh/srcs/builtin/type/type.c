/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 11:43:36 by araout            #+#    #+#             */
/*   Updated: 2019/09/23 08:26:05 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int			check_alias(char *str)
{
	int				i;
	unsigned int	len;

	i = -1;
	if (!g_shell.aliasp)
		return (0);
	len = ft_strlen(str);
	while (g_shell.aliasp[++i])
	{
		if ((ft_strlen(g_shell.aliasp[i]) > len)\
				&& (!ft_strncmp(str, g_shell.aliasp[i], len)))
		{
			ft_printf("%s is aliased to \'%s\'\n", str,
				&g_shell.aliasp[i][len + 1]);
			return (1);
		}
	}
	return (0);
}

int			check_built_in(char *args)
{
	int		j;

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

int			check_path_abs(char *args)
{
	struct stat	buf;

	if (!stat(args, &buf) && S_ISREG(buf.st_mode))
	{
		ft_printf("%s is %s\n", args, args);
		return (1);
	}
	return (0);
}

int			check_path_var(char *args, char *path)
{
	char		**split_path;
	int			i;
	char		*tmp;
	struct stat	buf;

	i = -1;
	split_path = ft_split(path, ":");
	ft_strdel(&path);
	while (split_path[++i])
	{
		tmp = ft_strjoin(split_path[i], "/");
		path = ft_strjoin(tmp, args);
		ft_strdel(&tmp);
		if (path && !stat(path, &buf) && S_ISREG(buf.st_mode))
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

int			type_main(char **args)
{
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	if (!args || !args[0] || !args[1])
		return (1);
	while (args[++i])
	{
		if (!check_built_in(args[i])
			&& !check_path_var(args[i], get_env_value("PATH"))
			&& !check_path_abs(args[i]) && !check_alias(args[i]))
		{
			ret = 1;
			ft_printf("%s not found\n", args[i]);
		}
	}
	return (ret);
}
