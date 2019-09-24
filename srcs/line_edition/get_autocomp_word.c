/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion_parser.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kicausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 04:46:11 by kicausse          #+#    #+#             */
/*   Updated: 2019/05/06 04:46:11 by kicausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_autocompletion_word(t_edit *line_e, unsigned int *argument,
		unsigned int *autocompletion_point)
{
	unsigned int i;
	unsigned int word_start;
	unsigned int word_end;
	unsigned int escape;
	unsigned int word_idx;

	if (line_e->line == NULL)
		return (NULL);
	i = 0;
	word_start = 0;
	word_end = 0;
	word_idx = 0;
	while (i < line_e->cursor_pos)
	{
		word_start = i;
		word_end = i;
		while (is_separator(line_e->line[i]) && i < line_e->cursor_pos)
		{
			if (line_e->line[i] == '\n' || line_e->line[i] == ';')
				word_idx = 0;
			++i;
		}
		if (i >= line_e->cursor_pos)
			break ;
		word_start = i;
		word_end = i;
		escape = 0;
		while (i < line_e->cursor_pos)
		{
			if (escape)
			{
				escape = 0;
				word_end = i++;
				continue ;
			}
			if (line_e->line[i] == '\\')
			{
				escape = 1;
				word_end = i++;
				continue ;
			}
			if (line_e->line[i] == '"' || line_e->line[i] == '\'')
			{
				quote_match(line_e->line, &i, line_e->cursor_pos,
							line_e->line[i]);
				word_end = i++;
				continue ;
			}
			if (is_separator(line_e->line[i]) || i >= line_e->cursor_pos)
				break ;
			word_end = i++;
		}
		++word_idx;
	}
	line_e->autocomp_quote = get_idx_quote_type(line_e->line, word_end);
	*argument = word_idx > 1;
	if (word_idx == 0 && word_start == word_end)
		return (NULL);
	if (word_start == word_end && is_separator(line_e->line[word_start]))
	{
		*autocompletion_point = word_start + 1;
		*argument = 1;
		return (ft_strnew(0));
	}
	*autocompletion_point = get_last_slash(line_e, word_start, word_end + 1);
	word_start = get_last_dollar(line_e, word_start, word_end + 1);
	return (parse_word(line_e->line + word_start, word_end - word_start + 1));
}
