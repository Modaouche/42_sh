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

void			print_file_type(t_file *file, int minlen)
{
	unsigned int i;

	if (file->type == 4 || file->type == 8)
		write(STDERR_FILENO, "\033[0m/", 5);
	else if (file->type == 6)
		write(STDERR_FILENO, "\033[0m%", 5);
	else if (file->type == 2)
		write(STDERR_FILENO, "\033[0m#", 5);
	else if (file->type == -2)
		write(STDERR_FILENO, "\033[0m@", 5);
	i = minlen - file->len - (file->type != 0) - 2;
	while (minlen > 0 && i-- > 0)
		write(STDERR_FILENO, " ", 1);
	tputs(tgetstr("me", NULL), 1, ft_puti);
	if (minlen != 0)
		write(STDERR_FILENO, "  ", 2);
}

/*
**  print_with_pad
**
**  - Prints a string with padding if the string is too short.
**    Also prints it's color and special character in case of
**    an executable or folder.
*/

void			print_with_pad(t_file *file, int minlen, int selected,
				unsigned int win_maxlen)
{
	if (file == NULL)
		return ;
	if ((file->type == 4 || file->type == 8) && !selected)
		ft_putstr_fd("\033[38;5;9m", STDERR_FILENO);
	else if ((file->type == 6 || file->type == 2) && !selected)
		ft_putstr_fd("\033[38;5;11m", STDERR_FILENO);
	else if ((file->type == -2) && !selected)
		ft_putstr_fd("\033[38;5;14m", STDERR_FILENO);
	if (file->len <= win_maxlen)
		write(STDERR_FILENO, file->name, file->len);
	else
	{
		if (win_maxlen > 4)
			write(STDERR_FILENO, file->name, win_maxlen - 4);
		write(STDERR_FILENO, "...", 3);
	}
	print_file_type(file, minlen);
}

/*
**  get_list_longest_word
**
**  - Gets the longest word in a list, required to have aligned columns.
*/

int				get_list_longest_word(t_file *list)
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
