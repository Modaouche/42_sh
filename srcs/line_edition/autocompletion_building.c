/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kicausse <kicausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 17:03:29 by kicausse          #+#    #+#             */
/*   Updated: 2019/05/14 01:48:52 by kicausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include <dirent.h>

/*
**  get_last_common_char
**
**  - Gets the last common character from a list.
**    Useful for partial autocompletion.
*/

int				get_last_common_char(t_file *list)
{
	int		last;
	char	c;
	t_file	*tmp;

	if (list == NULL || list->name == NULL)
		return (1);
	last = 0;
	while (list->name[last] != '\0')
	{
		tmp = list;
		c = ft_tolower(list->name[last]);
		while (tmp != NULL)
		{
			if (tmp->name == NULL || ft_tolower(tmp->name[last]) != c)
				return (last);
			tmp = tmp->next;
		}
		++last;
	}
	return (last);  
}

/*
**  search_similar_files
**
**  - Looks out for files that start with  the same first [len]
**    letters as the given string, in the given path.
*/

unsigned int	search_similar_files(int *cont, t_file **list, char *path,
				char *str, int len)
{
	DIR				*d;
	struct dirent	*f;
	unsigned int	size;
	int				type;

	if (!(d = opendir(path)))
		return (0);
	size = 0;
	while (*cont && (f = readdir(d)) != NULL)
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

int				search_similar_env_var(int *cont, t_file **list,
				char *str, int len, char **env)
{
	int		size;
	int		i;

	size = 0;
	while (*env != NULL && *cont)
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

/*
**  search_similar_builtin_aliases
**
**  - Adds builtins and alises into the autocompletion list
*/

int				search_similar_builtin_aliases(int *cont, t_file **list, char *str, int len)
{
	int size;
	int	i;
	int n;

	size = 0;
	i = 0;
	while (g_shell.fptr->flag[i] && *cont != 0)
	{
		if (ft_strncmp_case(str, g_shell.fptr->flag[i], len) == 0
			&& ft_file_list_append(list, g_shell.fptr->flag[i], 0))
			++size;
		++i;
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
	return (size);
}

/*
**  build_completion_list
**
**  - Builds the completion list by looking into the environment,
**    identifying each path and feeding them to the above function.
*/

t_file			*build_completion_list(int *cont, char *str,
				int len, char **env, unsigned int *list_size)
{
	t_file	*list;
	char	*path;
	int		i;

	if (env == NULL)
		return (NULL);
	list = NULL;
	*list_size = search_similar_env_var(cont, &list, str, len, env);
	while (*env != NULL && ft_strncmp(*env, "PATH=", 5) != 0)
		++env;
	if (*env == NULL)
		return (NULL);
	path = *env + 5;
	while (*path != 0 && *cont)
	{
		i = 0;
		while (path[i] != ':' && path[i] != '\0')
			++i;
		if (path[i] == ':')
		{
			path[i] = '\0';
			*list_size += search_similar_files(cont, &list, path, str, len);
			path[i] = ':';
			++i;
		}
		else
			*list_size += search_similar_files(cont, &list, path, str, len);
		path += i;
	}
	*list_size += search_similar_builtin_aliases(cont, &list, str, len);
	return (list);
}

/*
**  build_completion_list_files
**
**  - Builds the completion list by looking by looking at the input
**    and searching files based on current written path
*/

t_file			*build_completion_list_files(int *cont, char *str, int len,
				unsigned int *list_size)
{
	t_file	*list;
	int 	last_slash;

	last_slash = len - 1;
	while (last_slash >= 0 && str[last_slash] != '/')
		--last_slash;
	list = NULL;
	*list_size = 0;
	if (last_slash < 0)
		*list_size += search_similar_files(cont, &list, ".", str, len);
	else
	{
		if (last_slash == 0)
		{
			*list_size += search_similar_files(cont, &list, "/",
						str + 1, len - 1);
		}
		else
		{
			str[last_slash] = '\0';
			*list_size += search_similar_files(cont, &list, str,
						str + last_slash + 1, len - last_slash - 1);
			str[last_slash] = '/';
		}
	}
	return (list);
}
