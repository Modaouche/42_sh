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

int		parse_chars(t_edit *line_e, t_autocomp_word *aw)
{
	if (aw->escape)
	{
		aw->escape = 0;
		aw->word_end = aw->i++;
	}
	else if (line_e->line[aw->i] == '\\')
	{
		aw->escape = 1;
		aw->word_end = aw->i++;
	}
	else if (line_e->line[aw->i] == '"' || line_e->line[aw->i] == '\'')
	{
		quote_match(line_e->line, &aw->i, line_e->cursor_pos,
					line_e->line[aw->i]);
		aw->word_end = aw->i++;
	}
	else if (is_separator(line_e->line[aw->i]) || aw->i >= line_e->cursor_pos)
		return (1);
	else
		aw->word_end = aw->i++;
	return (0);
}

char	*get_return_value(t_edit *line_e, t_autocomp_word *aw,
		unsigned int *argument, unsigned int *autocompletion_point)
{
	line_e->autocomp_quote = get_idx_quote_type(line_e->line, aw->word_end);
	*argument = aw->word_idx > 1;
	if (aw->word_idx == 0 && aw->word_start == aw->word_end)
		return (NULL);
	if (aw->word_start == aw->word_end
		&& is_separator(line_e->line[aw->word_start]))
	{
		*autocompletion_point = aw->word_start + 1;
		*argument = 1;
		return (ft_strnew(0));
	}
	*autocompletion_point = get_last_slash(line_e,
							aw->word_start, aw->word_end + 1);
	aw->word_start = get_last_dollar(line_e, aw->word_start,
							aw->word_end + 1);
	return (parse_word(line_e->line + aw->word_start,
							aw->word_end - aw->word_start + 1));
}

char	*get_autocompletion_word(t_edit *line_e, unsigned int *argument,
		unsigned int *autocompletion_point)
{
	t_autocomp_word	aw;

	if (line_e->line == NULL)
		return (NULL);
	ft_bzero(&aw, sizeof(t_autocomp_word));
	while (aw.i < line_e->cursor_pos)
	{
		aw.word_start = aw.i;
		aw.word_end = aw.i;
		while (is_separator(line_e->line[aw.i]) && aw.i < line_e->cursor_pos)
		{
			if (line_e->line[aw.i] == '\n' || line_e->line[aw.i] == ';')
				aw.word_idx = 0;
			++aw.i;
		}
		if (aw.i >= line_e->cursor_pos)
			break ;
		aw.word_start = aw.i;
		aw.word_end = aw.i;
		aw.escape = 0;
		while (aw.i < line_e->cursor_pos && !parse_chars(line_e, &aw))
			;
		++aw.word_idx;
	}
	return (get_return_value(line_e, &aw, argument, autocompletion_point));
}
