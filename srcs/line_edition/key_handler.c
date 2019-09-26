/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 17:03:29 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 01:48:52 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		remove_char(t_edit *line_e)
{
	cursor_move_to(line_e, line_e->cursor_pos - 1);
	tputs(tgetstr("cd", NULL), 1, ft_puti);
	line_e->len -= 1;
	if (line_e->line[0])
	{
		ft_strcpy(line_e->line + (line_e->cursor_pos),\
				line_e->line + (line_e->cursor_pos + 1));
	}
	print_line(line_e, line_e->cursor_pos);
	cursor_move_from_to(line_e, line_e->len, line_e->cursor_pos);
	if (line_e->search_mode == 1)
		show_hist_line(line_e);
}

void		key_shortcut_handler3(t_edit *line_e, char *prevkey, char *key)
{
	(void)prevkey;
	if (ft_strlen(key) == 1)
	{
		if (*key == 18 && line_e->search_mode != 1)
		{
			cancel_autocompletion(line_e);
			line_e->search_mode = 1;
			show_hist_line(line_e);
		}
		if (line_e->line && *key == S_KEY_ERASE)
		{
			if (line_e->cursor_pos <= 1)
			{
				if (line_e->autocomp > 0 || line_e->search_mode)
					cancel_autocompletion(line_e);
				line_e->history_pos = 0;
			}
			if (line_e->cursor_pos == 0)
				return ;
			if (line_e->autocomp > 0)
				line_e->autocomp = 0;
			remove_char(line_e);
		}
	}
}

void		key_shortcut_handler2(t_edit *line_e, char *prevkey, char *key)
{
	if (ft_strlen(key) == 4)
	{
		if (line_e->autocomp < 2)
		{
			if (ft_memcmp(key, "\x1B\x5B\x36\x7E", 4))
				cursor_move_to(line_e, 0);
			else if (ft_memcmp(key, "\x1B\x5B\x35\x7E", 4))
				cursor_move_to(line_e, line_e->len);
			return ;
		}
		if (ft_memcmp(key, "\x1B\x5B\x35\x7E", 4) == 0)
			change_autocomp_idx(line_e, -line_e->winsize_row);
		else if (ft_memcmp(key, "\x1B\x5B\x36\x7E", 4) == 0)
			change_autocomp_idx(line_e, line_e->winsize_row);
	}
	else if (ft_strlen(key) == 3 && !ft_memcmp(key, "\x1B\x5B\x5A", 3)
		&& (line_e->autocomp == 2 || !ft_strcmp(prevkey, "\t")))
	{
		if (line_e->autocomp != 2)
			line_e->autocomp = 2;
		change_autocomp_idx(line_e, -1);
	}
	key_shortcut_handler3(line_e, prevkey, key);
}

void		key_shortcut_handler(t_edit *line_e, char *prevkey, char *key)
{
	if (ft_strlen(key) == 6)
	{
		if (!ft_memcmp(key, "\x1B\x5B\x31\x3B\x32", 5) && line_e->autocomp < 2)
		{
			if (key[5] == 0x43)
				go_to_next_word(line_e);
			else if (key[5] == 0x44)
				go_to_prev_word(line_e);
			else if (key[5] == 0x41)
				go_to_prev_line(line_e);
			else if (key[5] == 0x42)
				go_to_next_line(line_e);
		}
		else if (!ft_memcmp(key, "\x1B\x5B\x31\x3B\x32", 5)
				&& line_e->autocomp >= 2)
		{
			if (key[5] == 0x43 || key[5] == 0x42)
				change_autocomp_idx(line_e, line_e->winsize_row);
			else if (key[5] == 0x44 || key[5] == 0x41)
				change_autocomp_idx(line_e, -line_e->winsize_row);
		}
	}
	key_shortcut_handler2(line_e, prevkey, key);
}

void		on_key_press(t_edit *line_e, char *prevkey, char *key)
{
	if (!key)
		return ;
	if (ft_strlen(key) <= 1 && (ft_isprint(*key)
		|| (can_insert_tabs(line_e) && *key == '\t') || *key == 0x0d))
	{
		insert_char(line_e, (*key == 0x0d) ? ('\n') : (*key));
		return ;
	}
	key_shortcut_handler(line_e, prevkey, key);
	if (ft_strlen(key) <= 1 && (key[0] == '\t' || key[0] == S_KEY_CTRL_D))
	{
		if (line_e->line == NULL)
			return ;
		if (line_e->autocomp == 2)
		{
			change_autocomp_idx(line_e, 1);
			return ;
		}
		start_autocomp(line_e, prevkey);
	}
	else if (is_arrow(key))
		arrows_handler(line_e, key);
}
