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

unsigned int	build_list_2(char *path, char *str, int len, t_file **list)
{
	unsigned int	size;
	int				i;

	size = 0;
	while (*path != 0 && g_shell.line_e->autocomp)
	{
		i = 0;
		while (path[i] != ':' && path[i] != '\0')
			++i;
		if (path[i] == ':')
		{
			path[i] = '\0';
			size += search_similar_files(list, path, str, len);
			path[i] = ':';
			++i;
		}
		else
			size += search_similar_files(list, path, str, len);
		path += i;
	}
	return (size + search_similar_builtin_aliases(list, str, len));
}

/*
**  build_completion_list
**
**  - Builds the completion list by looking into the environment,
**    identifying each path and feeding them to the above function.
*/

t_file			*build_completion_list(char *str, int len,
				unsigned int *list_size)
{
	t_file	*list;
	char	*path;
	char	**env;

	if ((env = g_shell.envp) == NULL)
		return (NULL);
	list = NULL;
	*list_size = search_similar_env_var(&list, str, len);
	while (*env != NULL && ft_strncmp(*env, "PATH=", 5) != 0)
		++env;
	if (*env == NULL)
		return (NULL);
	path = *env + 5;
	*list_size += build_list_2(path, str, len, &list);
	return (list);
}

/*
**  build_completion_list_files
**
**  - Builds the completion list by looking by looking at the input
**    and searching files based on current written path
*/

t_file			*build_completion_list_files(char *str, int len,
				unsigned int *list_size)
{
	t_file	*list;
	int		last_slash;

	last_slash = len - 1;
	while (last_slash >= 0 && str[last_slash] != '/')
		--last_slash;
	list = NULL;
	*list_size = 0;
	if (last_slash < 0)
		*list_size += search_similar_files(&list, ".", str, len);
	else
	{
		if (last_slash == 0)
			*list_size += search_similar_files(&list, "/", str + 1, len - 1);
		else
		{
			str[last_slash] = '\0';
			*list_size += search_similar_files(&list, str,
						str + last_slash + 1, len - last_slash - 1);
			str[last_slash] = '/';
		}
	}
	return (list);
}
