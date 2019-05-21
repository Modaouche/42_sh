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
		ft_putstr_fd("\033[38;5;9m", 0);
	else if ((file->type == 6 || file->type == 2) && !selected)
		ft_putstr_fd("\033[38;5;11m", 0);
	else if ((file->type == -2) && !selected)
		ft_putstr_fd("\033[38;5;14m", 0);
	write(0, file->name, file->len);
	if (file->type == 4 || file->type == 8)
		write(0, "\033[0m/", 5);
	else if (file->type == 6)
		write(0, "\033[0m%", 5);
	else if (file->type == 2)
		write(0, "\033[0m#", 5);
	else if (file->type == -2)
		write(0, "\033[0m@", 5);
	i = minlen - file->len - (file->type != 0) - 2;
	while (i > 0)
	{
		write(0, " ", 1);
		--i;
	}
	tputs(tgetstr("me", NULL), 1, ft_puti);	
	write(0, "  ", 2);
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
**  print_autocompletion_list
**
**  - Moves the cursor under the line edition, clears everything under
**    the cursor and prints the list stored in autocompletion_list,
**    then moves the cursor back to where it was.
*/

void			print_autocompletion_list(t_edit *line_e, int highlight)
{
	t_file			*list;
	int				i;
	int				column;
	unsigned int	maxcol;
	int				maxrow;
	unsigned int	max;
	struct winsize	size;

	cursor_after(line_e);
	list = line_e->autocompletion_list;
	max = get_list_longest_word(list);
	ioctl(0, TIOCGWINSZ, &size);
	maxcol = size.ws_col / max;
	maxrow = (line_e->autocompletion_size / maxcol);
	line_e->autocompletion_maxcol = maxcol;
	line_e->autocompletion_maxrow = maxrow;
	column = 0;
	while (column <= maxrow)
	{
		i = column;
		while ((list = ft_file_list_at(line_e->autocompletion_list, i)))
		{
			if (i == highlight)
				tputs(tgetstr("mr", NULL), 1, ft_puti);
			print_with_pad(list, max, i == highlight);
			i += maxrow + 1;
		}
		if (++column <= maxrow)
		{
			tputs(tgetstr("do", NULL), 1, ft_puti);
			tputs(tgetstr("cr", NULL), 1, ft_puti); 
		}
	}
	while (--column >= 0)
		tputs(tgetstr("up", NULL), 1, ft_puti);
	cursor_actualpos(line_e);
}
