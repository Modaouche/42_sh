/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_comp_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kicausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 00:15:38 by kicausse          #+#    #+#             */
/*   Updated: 2019/09/25 00:15:39 by kicausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			init_column_sizes(t_edit *line_e, t_comp_print *comp)
{
	cursor_after(line_e);
	comp->max_length = get_list_longest_word(line_e->autocomp_list);
	if (comp->max_length > line_e->winsize_col)
	{
		comp->max_length = 0;
		comp->maxcol = 1;
	}
	else
		comp->maxcol = line_e->winsize_col / comp->max_length;
	comp->maxrow = (line_e->autocomp_size / comp->maxcol);
	if (comp->maxrow == 0)
		comp->maxrow = 1;
	line_e->autocomp_maxcol = comp->maxcol;
	line_e->autocomp_maxrow = comp->maxrow;
	comp->column = 0;
	comp->column_end = comp->maxrow;
	comp->page = 0;
	comp->newlines = 1;
}

void			get_page_count(t_edit *line_e, t_comp_print *comp)
{
	if (comp->maxrow >= line_e->winsize_row)
	{
		if (line_e->winsize_row > 2)
			comp->window_maxrow = (line_e->winsize_row - 2);
		else
			comp->window_maxrow = 1;
		if (comp->window_maxrow > get_line_height(line_e, -1))
			comp->window_maxrow -= get_line_height(line_e, -1);
		comp->maxpage = comp->maxrow / comp->window_maxrow;
		comp->page = (line_e->autocomp_idx
					% (comp->maxrow + 1)) / comp->window_maxrow;
		if (comp->page > comp->maxpage)
			comp->page = comp->maxpage;
		comp->column = comp->page * comp->window_maxrow;
		comp->column_end = comp->column + comp->window_maxrow;
		ft_printf_fd(STDERR_FILENO, "Page %d/%d",
				comp->page + 1, comp->maxpage + 1);
		++comp->newlines;
		tputs(tgetstr("ce", NULL), 1, ft_puti);
		ft_nlcr();
	}
	tputs(tgetstr("vi", NULL), 1, ft_puti);
}

void			go_back_up(t_edit *line_e, int newlines)
{
	tputs(tgetstr("cd", NULL), 1, ft_puti);
	while (newlines-- > 0)
		tputs(tgetstr("up", NULL), 1, ft_puti);
	cursor_reset_x_pos(line_e);
	tputs(tgetstr("ve", NULL), 1, ft_puti);
}

void			print_comp_list(t_edit *line_e, int highlight)
{
	t_comp_print comp;

	if (line_e->autocomp_size <= 1 || line_e->autocomp_list == NULL)
		return ;
	init_column_sizes(line_e, &comp);
	get_page_count(line_e, &comp);
	while (comp.column <= comp.column_end)
	{
		comp.i = comp.column;
		while (comp.i < (int)line_e->autocomp_size)
		{
			if (comp.i == highlight)
				tputs(tgetstr("mr", NULL), 1, ft_puti);
			print_with_pad(ft_file_list_at(line_e->autocomp_list, comp.i),
				comp.max_length, comp.i == highlight, line_e->winsize_col);
			comp.i += comp.maxrow + 1;
		}
		tputs(tgetstr("ce", NULL), 1, ft_puti);
		if (++comp.column <= comp.column_end)
		{
			++comp.newlines;
			ft_nlcr();
		}
	}
	go_back_up(line_e, comp.newlines);
}
