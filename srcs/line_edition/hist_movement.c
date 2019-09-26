/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gist_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 17:03:29 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 01:48:52 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		show_hist_line(t_edit *line_e)
{
	char	*str;

	if (line_e->len == 0 || line_e->line == NULL)
		str = "";
	else if ((str = get_hist_line_from_str(line_e->line)) == NULL)
		str = "Not found.";
	cursor_after(line_e);
	ft_putstr("History search: ");
	ft_putstr(str);
	tputs(tgetstr("cd", NULL), 1, ft_puti);
	cursor_move_from_to2(ft_strlen("History search: "),
						str, ft_strlen(str), 0);
	cursor_move_from_to(line_e, line_e->len, line_e->cursor_pos);
	tputs(tgetstr("up", NULL), 1, ft_puti);
}

void		get_hist_line(t_edit *line_e, int offset)
{
	char	*str;

	if (!g_shell.history)
		return ;
	str = get_hist_line_from_end(line_e->history_pos + offset);
	if (str == NULL)
	{
		if (offset < 0)
			line_e->history_pos = 0;
		return ;
	}
	if (line_e->history_pos == 0 && offset < 0)
		str = "";
	else
		line_e->history_pos += offset;
	replace_line_raw(line_e, ft_strdup(str));
	cancel_autocompletion(line_e);
}

void		replace_line_with_search(t_edit *line_e)
{
	char *str;

	if (!line_e->line || !(str = get_hist_line_from_str(line_e->line)))
		str = "";
	cursor_start(line_e);
	ft_strdel(&line_e->line);
	line_e->line = ft_strdup(str);
	line_e->len = ft_strlen(str);
	line_e->cursor_pos = line_e->len;
	line_e->search_mode = 0;
	print_line(line_e, 0);
	cancel_autocompletion(line_e);
}
