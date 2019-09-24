/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
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
**  quote_match
**
**  - Used during parsing when encountering a quote, it automatically skips
**  to the matching closing quote. Required to avoid parsing special
**  characters it may contain that could be considered as
**  a separator for example.
*/

int		quote_match(char *line, unsigned int *i, unsigned int maxlen, char c)
{
	unsigned int escape;

	escape = 0;
	while (++(*i) < maxlen)
	{
		if (escape == 1)
		{
			escape = 0;
			continue ;
		}
		if (line[*i] == '\\' && c == '"')
		{
			escape = 1;
			continue ;
		}
		if (line[*i] == c)
			break ;
	}
	return (c == '"' ? 1 : 2);
}

/*
**  get_idx_quote_type
**
**  - When given a position inside the given string, will determine
**    whether this position is surrounded by single, double or no quotes.
**    Very important for a lot of stuff concerning autocompletion with quotes.
*/

int		get_idx_quote_type(char *line, unsigned int idx)
{
	t_a gi;

	ft_bzero(&gi, sizeof(t_a));
	while (gi.i < idx && line[gi.i])
	{
		if (gi.escape || line[gi.i] == '\\')
		{
			gi.escape = !gi.escape;
			if (line[gi.i] == '\\')
				gi.quote = 0;
			++gi.i;
		}
		else if (line[gi.i] == '"' || line[gi.i] == '\'')
		{
			gi.quote = quote_match(line, &gi.i, idx, line[gi.i]);
			++gi.i;
		}
		else if (gi.i++ >= idx)
			break ;
		else
			gi.quote = 0;
	}
	return (gi.quote);
}

/*
**  re_print_prompt
**
**  - Re-prints the prompt regardless of cursor position
*/

void	re_print_prompt(t_edit *line_e)
{
	if (line_e->line == NULL)
		return ;
	cursor_start(line_e);
	while (g_shell.prompt_size > 0)
	{
		tputs(tgetstr("le", NULL), 1, ft_puti);
		--g_shell.prompt_size;
	}
	g_shell.prompt_size = print_prompt(0);
	cursor_move_from_to(line_e, 0, line_e->cursor_pos);
}

void	re_print_line(t_edit *line_e)
{
	if (line_e->line == NULL)
		return ;
	cursor_start(line_e);
	print_line(line_e, 0);
	cursor_move_from_to(line_e, line_e->len, line_e->cursor_pos);
}
