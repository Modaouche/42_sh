/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_insertion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 17:03:29 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 01:48:52 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			malloc_new_line(t_edit *line_e)
{
	char *new;

	line_e->len_max += BUFFER_LEN;
	if (!(new = ft_strnew(line_e->len_max)))
		return (0);
	ft_memcpy(new, line_e->line, line_e->len);
	ft_strdel(&(line_e->line));
	line_e->line = new;
	return (1);
}

int			append_to_line(t_edit *line_e, const char to_add)
{
	char	*new;

	if (!line_e->line)
	{
		if (!(line_e->line = ft_strnew(BUFFER_LEN)))
			return (0);
		line_e->line[0] = to_add;
		return (line_e->len = 1);
	}
	if (line_e->len >= line_e->len_max && !malloc_new_line(line_e))
		return (0);
	if (!(new = (char *)ft_memalloc(line_e->len_max)))
		return (0);
	ft_memcpy(new, line_e->line, line_e->cursor_pos);
	new[line_e->cursor_pos] = to_add;
	ft_memcpy(new + (line_e->cursor_pos + 1), line_e->line\
			+ line_e->cursor_pos, line_e->len - line_e->cursor_pos);
	ft_strdel(&(line_e->line));
	line_e->line = new;
	return (!!(line_e->len += 1));
}

void		insert_char(t_edit *line_e, char c)
{
	if (!(append_to_line(line_e, c)))
		le_exit(ER_MALLOC);
	if (c == '\n')
	{
		tputs(tgetstr("ce", NULL), 1, ft_puti);
		ft_nlcr();
	}
	else if (c == '\t')
		write(STDERR_FILENO, TAB_CHARS, TAB_LEN);
	else
		write(STDERR_FILENO, &c, 1);
	if (++line_e->cursor_pos != line_e->len)
	{
		print_line(line_e, line_e->cursor_pos);
		cursor_move_from_to(line_e, line_e->len, line_e->cursor_pos);
	}
	if (line_e->autocomp != 0)
		cancel_autocompletion(line_e);
	if (get_line_height(line_e, line_e->len) !=
		get_line_height(line_e, line_e->len - 1)
		&& c != '\n')
		ft_nlcr();
	if (line_e->search_mode == 1)
		show_hist_line(line_e);
}

int			can_insert_tabs(t_edit *line_e)
{
	unsigned int i;

	if (line_e->line == NULL || line_e->len == 0)
		return (1);
	i = 0;
	while (i < line_e->cursor_pos)
	{
		if (line_e->line[i] != ' ' && line_e->line[i] != '\t')
			return (0);
		++i;
	}
	return (1);
}
