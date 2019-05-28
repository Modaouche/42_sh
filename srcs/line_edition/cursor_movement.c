/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kicausse <kicausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 17:03:29 by kicausse          #+#    #+#             */
/*   Updated: 2019/04/25 19:19:49 by kicausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**   cursor_start
**
** - Move the terminal cursor to the start of the line edition
**   The cursor must be at it's genuine position (cursor_pos) for this to work
**   The cursor only needs to be at it's correct vertical position
*/

void		cursor_start(t_edit *line_e)
{
	unsigned int	i;
	unsigned int	x;

	if (line_e->line == NULL)
		return ;
	i = 0;
	x = line_e->prompt_size;
	while (i < line_e->cursor_pos)
	{
		if (line_e->line[i++] == '\n' || x >= line_e->winsize_col)
		{
			x = 0;
			tputs(tgetstr("up", NULL), 1, ft_puti);
		}
		else
			++x;
	}
	if (x == line_e->winsize_col && line_e->cursor_pos != line_e->len)
		tputs(tgetstr("up", NULL), 1, ft_puti);
	tputs(tgetstr("cr", NULL), 1, ft_puti); //start of line
	i = 0;
	while (i++ < line_e->prompt_size)
		tputs(tgetstr("nd", NULL), 1, ft_puti); //go right
}

/*	
**   cursor_end
**
** - Move the cursor to the last character of the line edition
**   The cursor must be at it's genuine position (cursor_pos) for this to work
**   The cursor only needs to be at it's correct vertical position
*/

void		cursor_end(t_edit *line_e)
{
	unsigned int	i;

	if (line_e->line == NULL)
		return ;
	i = get_line_height(line_e, line_e->len)
		- get_line_height(line_e, line_e->cursor_pos);
	while (i-- > 0)
		tputs(tgetstr("do", NULL), 1, ft_puti);
	cursor_reset_x_pos(line_e);
}

/*	
**   cursor_after
**
** - Move the cursor to be a line under the line edition
**   The cursor must be at it's genuine position (cursor_pos) for this to work
**   The cursor only needs to be at it's correct vertical position
*/

void		cursor_after(t_edit *line_e)
{
	unsigned int	i;

	if (line_e->line == NULL)
		return ;
	i = get_line_height(line_e, line_e->len) + 1
		- get_line_height(line_e, line_e->cursor_pos);
	while (i != 0)
	{
		tputs(tgetstr("do", NULL), 1, ft_puti);
		--i;
	}
	tputs(tgetstr("cr", NULL), 1, ft_puti);
}

/*
**  cursor_reset_x_pos
**
**  - Move the cursor to it's correct horizontal position.
*/

void		cursor_reset_x_pos(t_edit *line_e)
{
	unsigned int x;

	tputs(tgetstr("cr", NULL), 1, ft_puti);
	x = get_position_x_index(line_e, line_e->cursor_pos);
	while (x-- > 0)
		tputs(tgetstr("nd", NULL), 1, ft_puti);
}

/*
**  cursor_move_to
**
**  - Move the cursor to a specific position
*/

void		cursor_move_to(t_edit *line_e, uint pos)
{
	int x;

	x = get_line_height(line_e, pos)
		- get_line_height(line_e, line_e->cursor_pos);
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
	x = get_position_x_index(line_e, pos);
	while (x-- > 0)
		tputs(tgetstr("nd", NULL), 1, ft_puti);
	line_e->cursor_pos = pos;
}
