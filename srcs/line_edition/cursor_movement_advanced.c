/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_movement_advanced.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kicausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 00:11:31 by kicausse          #+#    #+#             */
/*   Updated: 2019/09/25 00:11:31 by kicausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**  cursor_move_from_to
**
**  - Move the cursor to a specific position from a specific other pos
**    Doesn't rely on cursor_pos or modify it in the process.
*/

void		cursor_move_from_to(t_edit *line_e, uint from, uint to)
{
	int x;

	x = get_line_height(line_e, to)
		- get_line_height(line_e, from);
	while (x > 0)
	{
		tputs(tgetstr("do", NULL), 1, ft_puti);
		--x;
	}
	while (x < 0)
	{
		tputs(tgetstr("up", NULL), 1, ft_puti);
		++x;
	}
	tputs(tgetstr("cr", NULL), 1, ft_puti);
	x = get_index_x_pos(line_e, to);
	while (x-- > 0)
		tputs(tgetstr("nd", NULL), 1, ft_puti);
}

void		cursor_move_from_to2(int prefix,
			char *str, uint from, uint to)
{
	int x;

	x = get_str_height(g_shell.line_e, prefix, str, to)
		- get_str_height(g_shell.line_e, prefix, str, from);
	while (x > 0)
	{
		tputs(tgetstr("do", NULL), 1, ft_puti);
		--x;
	}
	while (x < 0)
	{
		tputs(tgetstr("up", NULL), 1, ft_puti);
		++x;
	}
	tputs(tgetstr("cr", NULL), 1, ft_puti);
	x = get_index_x_pos(g_shell.line_e, to);
	while (x-- > 0)
		tputs(tgetstr("nd", NULL), 1, ft_puti);
}
