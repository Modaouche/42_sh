/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 17:03:29 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 01:48:52 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		go_to_prev_word(t_edit *line_e)
{
	unsigned int i;
	unsigned int word_start;
	unsigned int last_word_start;
	unsigned int escape;

	i = 0;
	escape = 0;
	word_start = 0;
	last_word_start = 0;
	while (i < line_e->cursor_pos)
	{
		if (escape == 1 || line_e->line[i] == '\\')
		{
			escape = !escape;
			++i;
			continue ;
		}
		if (line_e->line[i] == '"' || line_e->line[i] == '\'')
		{
			quote_match(line_e->line, &i, line_e->cursor_pos, line_e->line[i]);
			if (i++ >= line_e->cursor_pos)
				break ;
		}
		if (is_separator(line_e->line[i]))
		{
			while (is_separator(line_e->line[i]))
				++i;
			last_word_start = word_start;
			word_start = i;
			continue ;
		}
		++i;
	}
	cursor_move_to(line_e, last_word_start);
}

void		go_to_next_word(t_edit *line_e)
{
	unsigned int i;
	unsigned int quote;
	unsigned int escape;

	i = line_e->cursor_pos;
	quote = get_idx_quote_type(line_e->line, i);
	if (quote)
	{
		quote_match(line_e->line, &i, line_e->len, "'\""[quote - 1]);
		++i;
	}
	escape = 0;
	while (i < line_e->len)
	{
		if (escape == 1 || line_e->line[i] == '\\')
		{
			escape = !escape;
			++i;
			continue ;
		}
		if (line_e->line[i] == '"' || line_e->line[i] == '\'')
		{
			quote_match(line_e->line, &i, line_e->len, line_e->line[i]);
			if (i < line_e->len)
				++i;
			continue ;
		}
		if (is_separator(line_e->line[i]))
		{
			while (is_separator(line_e->line[i]))
				++i;
			break ;
		}
		++i;
	}
	cursor_move_to(line_e, i);
}
