/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 17:03:29 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 01:48:52 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	arrows_handler2(t_edit *line_e, char *key)
{
	if (key[2] == S_KEY_ARW_UP)
	{
		if (line_e->autocomp == 2)
			change_autocomp_idx(line_e, -1);
		else
			get_hist_line(line_e, 1);
	}
	else if (key[2] == S_KEY_ARW_DOWN)
	{
		if (line_e->autocomp == 2)
			change_autocomp_idx(line_e, 1);
		else
			get_hist_line(line_e, -1);
	}
}

void	arrows_handler(t_edit *line_e, char *key)
{
	if (line_e->line && key[2] == S_KEY_ARW_LEFT)
	{
		if (line_e->autocomp == 2)
		{
			if (line_e->autocomp_idx > line_e->autocomp_maxrow)
				change_autocomp_idx(line_e, -(line_e->autocomp_maxrow + 1));
		}
		else if (line_e->cursor_pos > 0)
			cursor_move_to(line_e, line_e->cursor_pos - 1);
	}
	else if (line_e->line && key[2] == S_KEY_ARW_RIGHT)
	{
		if (line_e->autocomp == 2)
		{
			if (line_e->autocomp_idx + (line_e->autocomp_maxrow + 1)
				< line_e->autocomp_size)
				change_autocomp_idx(line_e, line_e->autocomp_maxrow + 1);
		}
		else if (line_e->cursor_pos < line_e->len)
			cursor_move_to(line_e, line_e->cursor_pos + 1);
	}
	else
		arrows_handler2(line_e, key);
}
