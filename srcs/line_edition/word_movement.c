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

int			skip_separators(t_edit *line_e, t_word_mov *pw)
{
	if (is_separator(line_e->line[pw->i]))
	{
		while (is_separator(line_e->line[pw->i]))
			++pw->i;
		pw->last_word_start = pw->word_start;
		pw->word_start = pw->i;
		return (1);
	}
	return (0);
}

void		go_to_prev_word(t_edit *line_e)
{
	t_word_mov	pw;

	ft_bzero(&pw, sizeof(pw));
	while (pw.i < line_e->cursor_pos)
	{
		if (pw.escape == 1 || line_e->line[pw.i] == '\\')
		{
			pw.escape = !pw.escape;
			++pw.i;
			continue ;
		}
		if (line_e->line[pw.i] == '"' || line_e->line[pw.i] == '\'')
		{
			quote_match(line_e->line, &pw.i,
				line_e->cursor_pos, line_e->line[pw.i]);
			if (pw.i++ >= line_e->cursor_pos)
				break ;
		}
		if (!skip_separators(line_e, &pw))
			++pw.i;
	}
	cursor_move_to(line_e, pw.last_word_start);
}

int			match_quotes_and_sep(t_edit *line_e, t_word_mov *pw)
{
	if (line_e->line[pw->i] == '"' || line_e->line[pw->i] == '\'')
	{
		quote_match(line_e->line, &pw->i, line_e->len, line_e->line[pw->i]);
		if (pw->i >= line_e->len)
			return (1);
	}
	if (is_separator(line_e->line[pw->i]))
	{
		while (is_separator(line_e->line[pw->i]))
			++pw->i;
		return (1);
	}
	return (0);
}

void		go_to_next_word(t_edit *line_e)
{
	t_word_mov	pw;

	pw.i = line_e->cursor_pos;
	if ((pw.quote = get_idx_quote_type(line_e->line, pw.i)))
	{
		quote_match(line_e->line, &pw.i, line_e->len, "'\""[pw.quote - 1]);
		++pw.i;
	}
	pw.escape = 0;
	while (pw.i < line_e->len)
	{
		if (pw.escape == 1 || line_e->line[pw.i] == '\\')
		{
			pw.escape = !pw.escape;
			++pw.i;
			continue ;
		}
		if (match_quotes_and_sep(line_e, &pw))
			break ;
		++pw.i;
	}
	cursor_move_to(line_e, pw.i);
}
