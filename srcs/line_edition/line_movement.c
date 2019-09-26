/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 17:03:29 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 01:48:52 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		go_to_prev_line(t_edit *line_e)
{
	unsigned int i;
	unsigned int x;
	unsigned int curr_height;
	unsigned int height;
	unsigned int newpos;

	if (line_e->line == NULL)
		return ;
	i = 0;
	newpos = 0;
	x = g_shell.prompt_size;
	curr_height = 0;
	height = get_line_height(line_e, line_e->cursor_pos);
	while ((i + 1) < line_e->cursor_pos && curr_height < height)
	{
		++x;
		if (line_e->line[i++] == '\n' || x >= line_e->winsize_col)
		{
			x = 0;
			if (++curr_height >= height)
				break ;
			newpos = i;
		}
	}
	cursor_move_to(line_e, newpos);
}

void		go_to_next_line(t_edit *line_e)
{
	unsigned int i;
	unsigned int x;

	if (line_e->line == NULL)
		return ;
	i = 0;
	x = g_shell.prompt_size;
	while (i < line_e->len)
	{
		if (line_e->line[i++] == '\n' || x >= line_e->winsize_col)
		{
			x = 0;
			if (i > line_e->cursor_pos)
				break ;
		}
	}
	cursor_move_to(line_e, i);
}
