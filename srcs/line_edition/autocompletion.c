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

/*
**  replace_word
**
**  - Replaces the word at the current cursor position with the
**    given one.
*/

void	replace_word(t_edit *line_e, char *new, size_t length, char *suffix)
{
	char			*str;

	if (line_e->autocomp_quote == 2)
		new = escape_singlequote(new, length);
	else if (line_e->autocomp_quote == 1)
		new = escape_name(new, AUTOCOMP_ESCAPED_CHARS_IN_DBLQUOTE, length);
	else
		new = escape_name(new, AUTOCOMP_ESCAPED_CHARS, length);
	if ((length = ft_strlen(new)) == 0)
		return ;
	if (!(str = ft_strnew(line_e->autocomp_point + length + ft_strlen(suffix)
		+ (line_e->autocomp_quote > 0))))
	{
		ft_strdel(&new);
		return ;
	}
	ft_memcpy(str, line_e->line, line_e->autocomp_point);
	ft_memcpy(str + line_e->autocomp_point, new, length);
	ft_strcat(str + line_e->autocomp_point + length, suffix);
	if (line_e->autocomp_quote == 1 && length != 0)
		ft_strcat(str + line_e->autocomp_point + length, "\"");
	else if (line_e->autocomp_quote == 2 && length != 0)
		ft_strcat(str + line_e->autocomp_point + length, "'");
	ft_strdel(&new);
	cursor_start(line_e);
	ft_strdel(&line_e->line);
	line_e->line = str;
	line_e->len = ft_strlen(str);
	line_e->cursor_pos = line_e->len;
	print_line(line_e, 0);
}
/*
**  replace_word_from_completion
**
**  - Replaces the word at the current cursor position with
**    the one at the current autocompletion cursor.
*/

void	replace_word_from_completion(t_edit *line_e)
{
	t_file			*file;

	file = ft_file_list_at(line_e->autocomp_list, line_e->autocomp_idx);
	if (file == NULL)
		return ;
	if (line_e->autocomp_size == 1 && (file->type == AUTOCOMP_TYPE_FOLDER
		|| file->type == AUTOCOMP_TYPE_FOLDER2))
		replace_word(line_e, file->name, ft_strlen(file->name), "/");
	else
		replace_word(line_e, file->name, ft_strlen(file->name), NULL);
}

t_file	*build_completion_list_env(char *str, char **env,
									uint *list_size, t_edit *line_e)
{
	t_file	*list;
	int		start;		

	*list_size = 0;
	if (*str == '\0' || env == NULL || *env == NULL)
		return (NULL);
	list = NULL;
	start = 1;
	if (str[0] != '0' && str[1] == '{')
	{
		start = 2;
		++line_e->autocomp_point;
	}
	*list_size = search_similar_env_var(&list, str + start, 
					ft_strlen(str + start), env);
	return (list);
}

/*
**  build_from_word
**
**  - The base of autocompletion, is what determines what is
**    the words that needs to be autocompleted based on
**    cursor position. Also determines whether it is
**    autocompleting an argument or an executable name,
**    and what part of the line is the autocompletion going to
**    replace.
*/

int 	build_list_from_word(t_edit *line_e)
{
	char			*word;
	unsigned int	comp_type;

	ft_file_list_delete(&line_e->autocomp_list);
	ft_bzero(&line_e->autocomp_list,
		(size_t)&line_e->autocomp_quote - (size_t)&line_e->autocomp_list);
	if ((word = get_autocompletion_word(line_e, &comp_type,
				&line_e->autocomp_point)) == NULL)
		return (0);
	if (word[0] == '/' || word[0] == '.')
		comp_type = 1;
	else if (word[0] == '$')
		comp_type = 2;
	if (comp_type == 0)
	{
		line_e->autocomp_list = build_completion_list(word,
									ft_strlen(word),
									line_e->env,
									&line_e->autocomp_size);
	}
	else if (comp_type == 1)
	{
		line_e->autocomp_list = build_completion_list_files(word,
									ft_strlen(word),
									&line_e->autocomp_size);
	}
	else
	{
		line_e->autocomp_list = build_completion_list_env(word,
								line_e->env,
								&line_e->autocomp_size, line_e);
	}
	line_e->autocomp_list = merge_sort(line_e->autocomp_list);
	ft_strdel(&word);
	return (line_e->autocomp_list == NULL ? 0 : 1);
}

/*
**
**  escape_singlequote
**
**  - Escapes the name's singlequotes by closing them, writing an
**    escaped singlequote then re-opening singlequotes.
*/

char 	*escape_singlequote(char *name, unsigned int max)
{
	unsigned int	x;
	unsigned int	i;
	char 			*new;

	i = 0;
	x = 0;
	while (name[i] && i < max)
	{
		if (name[i++] == '\'')
			x += 3;
		++x;
	}
	if ((new = ft_strnew(x)) == NULL)
		return (NULL);
	x = 0;
	i = 0;
	while (name[i] && i < max)
	{ 
		if (name[i] == '\'')
		{
			ft_memcpy(new + x, "'\\''", 4);
			x += 4;
			++i;
		}
		else
			new[x++] = name[i++];
	}
	return (new);
}

/*
**
**  escape_name
**
**  - Escapes the name's special characters for proper autocompletion purposes.
**    Escapes based on the given charset.
*/

char	*escape_name(char *name, char *escaped_chars, unsigned int max)
{
	unsigned int x;
	unsigned int i;
	char *new;

	i = 0;
	x = 0;
	while (name[i] && i < max)
	{
		if (ft_cfind(escaped_chars, name[i++]) != -1)
			++x;
		++x;
	}
	if ((new = ft_strnew(x)) == NULL)
		return (NULL);
	x = 0;
	i = 0;
	while (name[i] && i < max)
	{ 
		if (ft_cfind(escaped_chars, name[i]) != -1)
			new[x++] = '\\';
		new[x++] = name[i++];
	}
	return (new);
}
