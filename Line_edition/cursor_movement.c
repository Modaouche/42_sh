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

#include "../includes/shell.h"

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
	struct winsize	size;

	if (line_e->line == NULL)
		return ;
	i = 0;
	x = line_e->prompt_size;
	ioctl(0, TIOCGWINSZ, &size);
	while (i < line_e->cursor_pos)
	{
		if (line_e->line[i] == '\n' || x >= size.ws_col)
		{
			x = 0;
			tputs(tgetstr("up", NULL), 1, ft_puti);
		}
		else
			++x;
		++i;
	}
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
	int				x;
	struct winsize	size;

	if (line_e->line == NULL)
		return ;
	cursor_start(line_e);
	i = 0;
	x = line_e->prompt_size;
	ioctl(0, TIOCGWINSZ, &size);
	while (line_e->line[i])
	{
		if (line_e->line[i] == '\n' || x >= size.ws_col)
		{
			x = 0;
			tputs(tgetstr("do", NULL), 1, ft_puti); //go down
		}
		else
			++x;
		++i;
	}
	tputs(tgetstr("cr", NULL), 1, ft_puti); //start of line
	while (x-- >= 0)
		tputs(tgetstr("nd", NULL), 1, ft_puti); //go right
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
	int				x;
	struct winsize	size;

	if (line_e->line == NULL)
		return ;
	cursor_start(line_e);
	i = 0;
	x = line_e->prompt_size;
	ioctl(0, TIOCGWINSZ, &size);
	while (line_e->line[i])
	{
		if (line_e->line[i] == '\n' || x >= size.ws_col)
		{
			x = 0;
			tputs(tgetstr("do", NULL), 1, ft_puti); //go down
		}
		else
			++x;
		++i;
	}
	tputs(tgetstr("do", NULL), 1, ft_puti); //go down
	tputs(tgetstr("cr", NULL), 1, ft_puti); //start of line
}

/*	
**   cursor_actualpos
**
** - Move the cursor to the cursor_pos
**   To be used when the cursor is at the correct line but wrong column
**
*/

void        cursor_actualpos(t_edit *line_e)
{
	unsigned int	i;
	unsigned int	x;
	struct winsize	size;

	cursor_start(line_e);
	i = 0;
	x = line_e->prompt_size;
	ioctl(0, TIOCGWINSZ, &size);
	while (i < line_e->cursor_pos)
	{
		if (line_e->line[i] == '\n' || x >= size.ws_col)
		{
			x = 0;
			tputs(tgetstr("do", NULL), 1, ft_puti); //go down
		}
		else
			++x;
		++i;
	}
	tputs(tgetstr("cr", NULL), 1, ft_puti); //start of line
	while (x > 0)
	{
		--x;
		tputs(tgetstr("nd", NULL), 1, ft_puti); //go right
	}
}