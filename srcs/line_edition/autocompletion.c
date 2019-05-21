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

void	replace_word(t_edit *line_e, char *new, size_t length)
{
	char			*str;

	str = ft_strnew(line_e->autocomp_point + length);
	if (str == NULL)
		toexit(line_e, "malloc");
	ft_memcpy(str, line_e->line, line_e->autocomp_point);
	ft_memcpy(str + line_e->autocomp_point, new, length);
	cursor_start(line_e);
	ft_strdel(&line_e->line);
	line_e->line = str;
	line_e->len = ft_strlen(line_e->line);
	line_e->cursor_pos = line_e->len;
	ft_putstr_fd(line_e->line, STDERR_FILENO);
	tputs(tgetstr("cd", NULL), 1, ft_puti);
}

/*
**  replace_word_from_completion
**
**  - Replaces the word at the current cursor position with
**    the one at the current autocompletion cursor.
*/

void	replace_word_from_completion(t_edit *line_e)
{
	char			*str;
	t_file			*file;

	file = ft_file_list_at(line_e->autocomp_list, line_e->autocomp_idx);
	if (file == NULL)
		return ;
	str = ft_strnew(line_e->autocomp_point + ft_strlen(file->name)
		+ (file->type == 4 || file->type == 8));
	if (str == NULL)
		toexit(line_e, "malloc");
	ft_memcpy(str, line_e->line, line_e->autocomp_point);
	ft_strcpy(str + line_e->autocomp_point, file->name);
	if (file->type == 4 || file->type == 8)
		ft_strcat(str, "/");
	cursor_start(line_e);
	ft_strdel(&line_e->line);
	line_e->line = str;
	line_e->len = ft_strlen(line_e->line);
	line_e->cursor_pos = line_e->len;
	ft_putstr_fd(line_e->line, STDERR_FILENO);
	tputs(tgetstr("cd", NULL), 1, ft_puti);
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

int 	build_from_word(t_edit *line_e)
{
	char			*word;
	unsigned int	argument;

	if ((word = get_autocompletion_word(line_e, &argument,
				&line_e->autocomp_point)) == NULL)
		return (0);
	if (word[0] == '/' || word[0] == '.')
		argument = 1;
	if (argument == 0)
	{
		line_e->autocomp_list = build_completion_list(word,
									ft_strlen(word),
									line_e->env,
									&line_e->autocomp_size);
	}
	else
	{
		line_e->autocomp_list = build_completion_list_files(word,
									ft_strlen(word),
									&line_e->autocomp_size);
	}
	ft_strdel(&word);
	return (1);
}
