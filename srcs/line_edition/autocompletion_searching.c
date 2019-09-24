/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion_searching.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kicausse <kicausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 17:03:29 by kicausse          #+#    #+#             */
/*   Updated: 2019/05/14 01:48:52 by kicausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "shell.h"

int				search_similar_intern_var(t_file **list, char *str,
				int len)
{
	int i;
	int n;
	int size;

	size = 0;
	i = -1;
	while (g_shell.intern_var && g_shell.intern_var[++i])
	{
		if ((n = ft_cfind(g_shell.intern_var[i], '=')) == -1)
			continue ;
		g_shell.intern_var[i][n] = '\0';
		if (ft_strncmp_case(str, g_shell.intern_var[i], len) == 0
			&& ft_file_list_append(list, g_shell.intern_var[i], 0))
			++size;
		g_shell.intern_var[i][n] = '=';
	}
	return (size);
}

int				search_similar_builtin_aliases(t_file **list,
				char *str, int len)
{
	int size;
	int	i;
	int n;

	size = 0;
	i = -1;
	while (g_shell.fptr->flag[++i] && g_shell.line_e->autocomp)
	{
		if (ft_strncmp_case(str, g_shell.fptr->flag[i], len) == 0
			&& ft_file_list_append(list, g_shell.fptr->flag[i], 0))
			++size;
	}
	i = -1;
	while (g_shell.aliasp && g_shell.aliasp[++i])
	{
		if ((n = ft_cfind(g_shell.aliasp[i], '=')) == -1)
			continue ;
		g_shell.aliasp[i][n] = '\0';
		if (ft_strncmp_case(str, g_shell.aliasp[i], len) == 0
			&& ft_file_list_append(list, g_shell.aliasp[i], 0))
			++size;
		g_shell.aliasp[i][n] = '=';
	}
	return (size + search_similar_intern_var(list, str, len));
}

/*
**  search_similar_files
**
**  - Looks out for files that start with  the same first [len]
**    letters as the given string, in the given path.
*/

unsigned int	search_similar_files(t_file **list, char *path,
				char *str, int len)
{
	DIR				*d;
	struct dirent	*f;
	unsigned int	size;
	int				type;

	if (!(d = opendir(path)))
		return (0);
	size = 0;
	while (g_shell.line_e->autocomp && (f = readdir(d)) != NULL)
	{
		if (f->d_name[0] == '.' && (!len || str[0] != '.'))
			continue ;
		if (ft_strncmp_case(f->d_name, str, len) == 0)
		{
			type = 8 - f->d_type;
			if (ft_file_list_append(list, f->d_name, type))
				++size;
		}
	}
	closedir(d);
	return (size);
}

/*
**   search_similar_env_var
**
** - Builds the completion list by looking into the environment,
**   specifically at the environment variables.
*/

int				search_similar_env_var(t_file **list,
				char *str, int len)
{
	int		size;
	int		i;
	char	**env;

	if ((env = g_shell.envp) == NULL)
		return (0);
	size = 0;
	while (*env != NULL && g_shell.line_e->autocomp)
	{
		if (ft_strncmp_case(*env, str, len) == 0)
		{
			i = 0;
			while (env[0][i] != '=' && env[0][i])
				++i;
			if (env[0][i] == '\0' || i == 0)
				continue ;
			env[0][i] = '\0';
			ft_file_list_append(list, *env, 0);
			env[0][i] = '=';
			++size;
		}
		++env;
	}
	return (size);
}
