/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kicausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 04:46:11 by kicausse          #+#    #+#             */
/*   Updated: 2019/05/06 04:46:11 by kicausse         ###   ########.fr       */
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
		c = list->name[last];
		while (tmp != NULL)
		{
			if (tmp->name == NULL || tmp->name[last] != c)
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
	while ((f = readdir(d)) != NULL)
	{
		if (f->d_name[0] == '.' && (!len || str[0] != '.'))
			continue ;
		if (ft_strncmp(f->d_name, str, len) == 0)
		{
			type = 8 - f->d_type;
			if (ft_file_list_append(list, f->d_name, type))
				++size;
		}
	}
	return (size);
}

/*
**   search_similar_env_var
**
** - Builds the completion list by looking into the environment,
**   specifically at the environment variables.
*/

int				search_similar_env_var(t_file **list, char *str, int len,
				char **env)
{
	int		size;
	int		i;

	size = 0;
	while (*env != NULL)
	{
		if (ft_strncmp(*env, str, len) == 0)
		{
			i = 0;
			while (env[0][i] != '=' && env[0][i])
				++i;
			if (env[0][i] == '\0' || i == 0)
				continue ;
			env[0][i + 1] = '\0';
			ft_file_list_append(list, *env, 9);
			env[0][i + 1] = '=';
			++size;
		}
		++env;
	}
	return (size);
}

/*
**  build_completion_list
**
**  - Builds the completion list by looking into the environment,
**    identifying each path and feeding them to the above function.
*/

t_file			*build_completion_list(char *str, int len, char **env,
				unsigned int *list_size)
{
	t_file	*list;
	char	*path;
	int		i;

	if (env == NULL)
		return (NULL);
	list = NULL;
	*list_size = search_similar_env_var(&list, str, len, env);
	while (*env != NULL && ft_strncmp(*env, "PATH=", 5) != 0)
		++env;
	if (*env == NULL)
		return (NULL);
	path = *env + 5;
	while (*path != 0)
	{
		i = 0;
		while (path[i] != ':' && path[i] != '\0')
			++i;
		if (path[i] == ':')
		{
			path[i] = '\0';
			*list_size += search_similar_files(&list, path, str, len);
			path[i] = ':';
			++i;
		}
		else
			*list_size += search_similar_files(&list, path, str, len);
		path += i;
	}
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
	int 	last_slash;

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
		{
			*list_size += search_similar_files(&list, "/",
						str + 1, len - 1);
		}
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

/*
**  replace_word
**
**  - Replaces the word at the current cursor position with the
**    given one.
*/

void			replace_word(t_edit *line_e, char *new)
{
	char			*str;

	str = ft_strnew(line_e->autocompletion_point + ft_strlen(new));
	if (str == NULL)
		toexit(line_e, "malloc");
	ft_memcpy(str, line_e->line, line_e->autocompletion_point);
	ft_strcpy(str + line_e->autocompletion_point, new);
	cursor_start(line_e);
	ft_strdel(&line_e->line);
	line_e->line = str;
	line_e->len = ft_strlen(line_e->line);
	line_e->cursor_pos = line_e->len;
	ft_putstr_fd(line_e->line, STDERR_FILENO);
	tputs(tgetstr("cd", NULL), 1, ft_puti);
}

/*
**  complete_from_word
**
**  - The base of autocompletion, is what determines what is
**    the words that needs to be autocompleted based on
**    cursor position. Also determines whether it is
**    autocompleting an argument or an executable name,
**    and what part of the line is the autocompletion going to
**    replace.
*/

int 			complete_from_word(t_edit *line_e)
{
	char			*word;
	unsigned int	argument;

	if ((word = get_autocompletion_word(line_e, &argument,
				&line_e->autocompletion_point)) == NULL)
		return (0);
	if (word[0] == '/' || word[0] == '.')
		argument = 1;
	if (argument == 0)
	{
		line_e->autocompletion_list = build_completion_list(word,
									ft_strlen(word),
									line_e->env,
									&line_e->autocompletion_size);
	}
	else
	{
		line_e->autocompletion_list = build_completion_list_files(word,
									ft_strlen(word),
									&line_e->autocompletion_size);
	}
	ft_strdel(&word);
	return (1);
}
