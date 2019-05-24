/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion_printing.c                          :+:      :+:    :+:   */
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
**  print_with_pad
**
**  - Prints a string with padding if the string is too short.
**    Also prints it's color and special character in case of
**    an executable or folder.
*/

void			print_with_pad(t_file *file, int minlen, int selected)
{
	unsigned int	i;

	if (file == NULL)
		return ;
	if ((file->type == 4 || file->type == 8) && !selected)
		ft_putstr_fd("\033[38;5;9m", STDERR_FILENO);
	else if ((file->type == 6 || file->type == 2) && !selected)
		ft_putstr_fd("\033[38;5;11m", STDERR_FILENO);
	else if ((file->type == -2) && !selected)
		ft_putstr_fd("\033[38;5;14m", STDERR_FILENO);
	write(STDERR_FILENO, file->name, file->len);
	if (file->type == 4 || file->type == 8)
		write(STDERR_FILENO, "\033[0m/", 5);
	else if (file->type == 6)
		write(STDERR_FILENO, "\033[0m%", 5);
	else if (file->type == 2)
		write(STDERR_FILENO, "\033[0m#", 5);
	else if (file->type == -2)
		write(STDERR_FILENO, "\033[0m@", 5);
	i = minlen - file->len - (file->type != 0) - 2;
	while (i > 0)
	{
		write(STDERR_FILENO, " ", 1);
		--i;
	}
	tputs(tgetstr("me", NULL), 1, ft_puti);	
	write(STDERR_FILENO, "  ", 2);
}

/*
**  get_list_longest_word
**
**  - Gets the longest word in a list, required to have aligned columns.
*/

int     		get_list_longest_word(t_file *list)
{
	unsigned int	longest;

	longest = 0;
	while (list)
	{
		if (list->len + (list->type != 0) > longest)
			longest = list->len + (list->type != 0);
		list = list->next;
	}
	return (longest + 2);
}

/*
**  print_comp_list
**
**  - Moves the cursor under the line edition, clears everything under
**    the cursor and prints the list stored in comp_list,
**    then moves the cursor back to where it was.
*/

void			print_comp_list(t_edit *line_e, int highlight)
{
	t_file			*list;
	int				i;
	unsigned int	column;
	unsigned int	column_end;
	unsigned int	maxcol;
	unsigned int	maxrow;
	unsigned int	max_length;
	unsigned int	page;
	unsigned int	maxpage;
	unsigned int	newlines;
	unsigned int	window_maxrow;
	
	if (line_e->autocomp_size <= 1 || !(list = line_e->autocomp_list))
		return ;
	cursor_after(line_e);
	max_length = get_list_longest_word(list);
	maxcol = line_e->winsize_col / max_length;
	if (maxcol == 0)
		maxcol = 1;
	maxrow = (line_e->autocomp_size / maxcol);
	if (maxrow == 0)
		maxrow = 1;
	line_e->autocomp_maxcol = maxcol;
	line_e->autocomp_maxrow = maxrow;
	column = 0;
	column_end = maxrow;
	page = 0;
	newlines = 1;
	if (maxrow >= line_e->winsize_row)
	{
		if (line_e->winsize_row > 2)
			window_maxrow = (line_e->winsize_row - 2);
		else
			window_maxrow = 1;
		if (window_maxrow > get_line_height(line_e))
			window_maxrow -= get_line_height(line_e);
		maxpage = maxrow / window_maxrow;
		page = (line_e->autocomp_idx % maxrow) / window_maxrow;
		if (page > maxpage)
			page = maxpage;
		column = page * window_maxrow;
		column_end = column + window_maxrow;
		ft_printf_fd(STDERR_FILENO, "Page %d/%d\n", page + 1, maxpage + 1);
		++newlines;
		tputs(tgetstr("cr", NULL), 1, ft_puti);
	}
	while (column <= column_end)
	{
		i = column;
		while (i < (int)line_e->autocomp_size)
		{
			list = ft_file_list_at(line_e->autocomp_list, i);
			if (i == highlight)
				tputs(tgetstr("mr", NULL), 1, ft_puti);
			print_with_pad(list, max_length, i == highlight);
			i += maxrow + 1;
		}
		if (++column <= column_end)
		{
			++newlines;
			tputs(tgetstr("do", NULL), 1, ft_puti);
			tputs(tgetstr("cr", NULL), 1, ft_puti); 
		}
	}
	while (newlines > 0)
	{
		tputs(tgetstr("up", NULL), 1, ft_puti);
		--newlines;	
	}
	cursor_actualpos(line_e);
}
