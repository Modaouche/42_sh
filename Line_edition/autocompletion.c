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

#include "../includes/shell.h"
#include "libft.h"
#include <dirent.h>

/*
**   get_last_common_char
**
** - Gets the last common character from a list,
**   Useful for autocompletion purposes
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
**   print_with_pad
**
** - Prints a string with padding if the string is too short.
**   Also prints it's color and special character in case of
**   an executable or folder.
*/

void			print_with_pad(t_file *file, int minlen, int selected)
{
	unsigned int	i;

	if (file->type == 4 && !selected)
		ft_putstr_fd("\033[38;5;9m", 2);
	write(0, file->name, file->len);
	if (file->type == 4)
		write(0, "\033[0m/", 5);
	i = minlen - file->len - (file->type != 0);
	while (i > 0)
	{
		write(0, " ", 1);
		--i;
	}
}

/*
**   get_list_longest_word
**
** - Gets the longest word in a list, required to have aligned columns
*/

int     		get_list_longest_word(t_file *list)
{
	unsigned int	longest;

	longest = 0;
	while (list)
	{
		if (list->len + (list->type != 0) > longest)
			longest = list->len + (list->type != 0);
		list = list->next;
	}
	return (longest + 2);
}

/*
**   print_autocompletion_list
**
** - Moves the cursor under the line edition, clears everything under
**   the cursor and prints the list stored in autocompletion_list,
**   then moves the cursor back to where it was.
*/

void			print_autocompletion_list(t_edit *line_e, int highlight)
{
	t_file			*list;
	int				i;
	int				newlines;
	unsigned int	maxcol;
	unsigned int	max;
	struct winsize	size;

	cursor_after(line_e);
	tputs(tgetstr("cd", NULL), 1, ft_puti);
	list = line_e->autocompletion_list;
	max = get_list_longest_word(list);
	ioctl(0, TIOCGWINSZ, &size);
	maxcol = size.ws_col / max;
	line_e->autocompletion_maxcol = maxcol;
	i = 0;
	newlines = 0;
	while (list)
	{
		if (i == highlight)
			tputs(tgetstr("mr", NULL), 1, ft_puti);
		print_with_pad(list, max, i++ == highlight);
		tputs(tgetstr("me", NULL), 1, ft_puti);
		list = list->next;
		if ((maxcol == 0 || i % maxcol == 0) && list != NULL)
		{
			++newlines;
			tputs(tgetstr("do", NULL), 1, ft_puti);
			tputs(tgetstr("cr", NULL), 1, ft_puti);    
		}
	}
	while (newlines-- >= 0)
		tputs(tgetstr("up", NULL), 1, ft_puti);
	cursor_actualpos(line_e);
}

/*
**   search_similar_files
**
** - Looks out for files that start with 
**   the same first [len] letters as the given string,
**   in the given path.
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
**   build_completion_list
**
** - Builds the completion list by looking into the environment,
**   identifying each path and feeding them to the above function.
*/

t_file			*build_completion_list(char *str, int len, char **env,
				unsigned int *list_size)
{
	t_file	*list;
	char	*path;
	int		i;

	list = NULL;
	if (env == NULL)
		return (NULL);
	while (*env != NULL && ft_strncmp(*env, "PATH=", 5) != 0)
		++env;
	if (*env == NULL)
		return (NULL);
	path = *env + 5;
	*list_size = 0;
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
**   build_completion_list_files
**
** - Builds the completion list by looking by looking at the input
**   and searching files based on current written path
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
		str[last_slash] = '\0';
		*list_size += search_similar_files(&list, str,
						str + last_slash + 1, len - last_slash - 1);
		str[last_slash] = '/';
	}
	return (list);
}

/*
**   replace_word
**
** - Replaces the word at the current cursor position with the
**   given one.
*/

void	replace_word(t_edit *line_e, char *new)
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
**   caca
**
** - The base of autocompletion, is what determines what is
**   the words that needs to be autocompleted based on
**   cursor position. Also determines whether it is
**   autocompleting an argument or an executable name.
*/

int 	caca(t_edit *line_e)
{
	unsigned int	argument;
	unsigned int	i;
	int 			tmp;

	if (line_e->cursor_pos == 0)
		return (0);
	i = 0;
	while (line_e->line[i] && i <= line_e->cursor_pos)
	{
		if (line_e->line[i] != ' ')
			break ;
		++i;
	}
	if (i >= line_e->cursor_pos || line_e->line[i] == '\0')
		return (0);
	argument = 0;
	i = line_e->cursor_pos;
	while (i > 0 && line_e->line[i] != ' ')
		--i;
	tmp = i - 1;
	while (tmp >= 0)
	{
		if (line_e->line[tmp] != ' ')
			argument = 1;
		--tmp;
	}
	if (i < line_e->cursor_pos && line_e->line[i] == ' ')
		++i;
	if (line_e->line[i] == '/' || line_e->line[i] == '.')
		argument = 1;
	if (argument == 0)
	{
		line_e->autocompletion_point = i;
		line_e->autocompletion_list = build_completion_list(line_e->line + i,
									line_e->cursor_pos - i,
									line_e->env,
									&line_e->autocompletion_size);
	}
	else
	{
		unsigned int last_slash;

		last_slash = i;
		tmp = i;
		while (tmp < (int)line_e->cursor_pos)
		{
			if (line_e->line[tmp] == '/')
				last_slash = tmp + 1;
			++tmp;
		}
		line_e->autocompletion_point = last_slash;
		line_e->autocompletion_list = build_completion_list_files(line_e->line + i,
									line_e->cursor_pos - i,
									&line_e->autocompletion_size);
	}
	return (1);
}
