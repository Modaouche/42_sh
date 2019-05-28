/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 17:03:29 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 01:48:52 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

/*
**  append_to_line
**
**  - Adds a character to the input line, and if necessary, reallocates the
**  line to fit it's new size.
*/

int		append_to_line(t_edit *line_e, const char to_add)
{
	char    *new;

	if (!line_e->line)
	{
		if (!(line_e->line = ft_strnew(BUFFER_LEN)))
			return (0);
		line_e->line[0] = to_add;
		line_e->len = 1;
		return (1);
	}
	if (line_e->len >= line_e->len_max)
	{
		line_e->len_max += BUFFER_LEN;
		if (!(new = ft_strnew(line_e->len_max)))
			return (0);
		ft_memcpy(new, line_e->line, line_e->len);
		ft_strdel(&(line_e->line));
		line_e->line = new;
	}
	if (!(new = (char *)ft_memalloc(line_e->len_max)))
		return (0);
	ft_memcpy(new, line_e->line, line_e->cursor_pos);
	new[line_e->cursor_pos] = to_add;
	ft_memcpy(new + (line_e->cursor_pos + 1), line_e->line\
		+ line_e->cursor_pos, line_e->len - line_e->cursor_pos);
	ft_strdel(&(line_e->line));
	line_e->line = new;
	line_e->len += 1;
	return (1);
}

/*
**  cancel_autocompletion
**
**  - Hides and free the current autocompletion.
*/

void	cancel_autocompletion(t_edit *line_e)
{
	unsigned int x;

	line_e->autocomp = 0;
	cursor_after(line_e);
	tputs(tgetstr("cd", NULL), 1, ft_puti);
	x = get_line_height(line_e, line_e->len)
		- get_line_height(line_e, line_e->cursor_pos) + 1;
	while (x-- > 0)
		tputs(tgetstr("up", NULL), 1, ft_puti);
	cursor_reset_x_pos(line_e);
	ft_file_list_delete(&line_e->autocomp_list);
}

/*
**  insert_char
**
**  - Called to insert a character to the line and update it visually
*/

void	insert_char(t_edit *line_e, char c)
{
	if (line_e->autocomp == 2)
	{
		line_e->autocomp = 0;
		print_comp_list(line_e, -1);
	}
	if (!(append_to_line(line_e, c)))
		toexit(line_e, "malloc", 0);
	write(STDERR_FILENO, &c, 1);
	if (c == '\n')
		tputs(tgetstr("cr", NULL), 1, ft_puti);
	if (++line_e->cursor_pos != line_e->len)
	{
		ft_putstr_fd(line_e->line + line_e->cursor_pos, STDERR_FILENO);
		cursor_move_from_to(line_e, line_e->len, line_e->cursor_pos);
	}
}

/*
**  can_insert_tabs
**
**  - Function that determines whether the line is empty or not.
*/

int		can_insert_tabs(t_edit *line_e)
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

void	go_to_prev_word(t_edit *line_e)
{
	unsigned int i;
	unsigned int word_start;
	unsigned int last_word_start;
	unsigned int escape;

	i = 0;
	escape = 0;
	word_start = 0;
	last_word_start = 0;
	while (i < line_e->cursor_pos)
	{
		if (escape == 1)
		{
			escape = 0;
			++i;
			continue ;
		}
		if (line_e->line[i] == '\\')
		{
			escape = 1;
			++i;
			continue ;
		}
		if (line_e->line[i] == '"' || line_e->line[i] == '\'')
		{
			quote_match(line_e->line, &i, line_e->cursor_pos, line_e->line[i]);
			if (i++ >= line_e->cursor_pos)
				break ;
		}
		if (is_separator(line_e->line[i]))
		{
			while (is_separator(line_e->line[i]))
				++i;
			last_word_start = word_start;
			word_start = i;
			continue ;
		}
		++i;
	}
	cursor_move_to(line_e, last_word_start);
}

void	go_to_next_word(t_edit *line_e)
{
	unsigned int i;
	unsigned int quote;
	unsigned int escape;

	i = line_e->cursor_pos;
	quote = get_idx_quote_type(line_e->line, i);
	if (quote)
	{
		quote_match(line_e->line, &i, line_e->len, "'\""[quote - 1]);
		++i;
	}
	escape = 0;
	while (i < line_e->len)
	{
		if (escape == 1)
		{
			escape = 0;
			++i;
			continue ;
		}
		if (line_e->line[i] == '\\')
		{
			escape = 1;
			++i;
			continue ;
		}
		if (line_e->line[i] == '"' || line_e->line[i] == '\'')
		{
			quote_match(line_e->line, &i, line_e->len, line_e->line[i]);
			if (i < line_e->len)
				++i;
			continue ;
		}
		if (is_separator(line_e->line[i]))
		{
			while (is_separator(line_e->line[i]))
				++i;
			break ;
		}
		++i;
	}
	cursor_move_to(line_e, i);
}

void	change_autocomp_idx(t_edit *line_e, int value)
{
	if (value < 0)
	{
		if ((uint)(-value) <= line_e->autocomp_idx)
			line_e->autocomp_idx += value;
		else
			line_e->autocomp_idx = line_e->autocomp_size - 1;
	}
	else if ((line_e->autocomp_idx += (uint)value) >= line_e->autocomp_size)
		line_e->autocomp_idx = 0;
	replace_word_from_completion(line_e);
	print_comp_list(line_e, line_e->autocomp_idx);
}

void	key_shortcut_handler(t_edit *line_e, char *prevkey, char *key)
{
	if (ft_strlen(key) == 6 && line_e->autocomp < 2
		&& !ft_memcmp(key, "\x1B\x5B\x31\x3B\x32", 5))
	{
		if (key[5] == 0x43)
			go_to_next_word(line_e);
		else if (key[5] == 0x44)
			go_to_prev_word(line_e);
	}
	else if (ft_strlen(key) == 4)
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
}

/*
**  on_key_press
**
**  - Event handler called whenever the user pressed a key.
**    used to happen input to line or to react to special characters.
*/

void	on_key_press(t_edit *line_e, char *prevkey, char *key)
{
	if (!key)
	{
		ft_putendl_fd("error : key :null", STDERR_FILENO);
		return ;
	}
	if (ft_strlen(key) <= 1 && (ft_isprint(key[0])
		|| (can_insert_tabs(line_e) && key[0] == '\t')))
	{
		if (*key == '+')
			*key = '\n';
		insert_char(line_e, *key);
		return ;
	}
	key_shortcut_handler(line_e, prevkey, key);
	if (ft_strlen(key) <= 1 && key[0] == '\t')
	{
		if (line_e->line == NULL)
			return ;
		if (line_e->autocomp == 2)
		{
			change_autocomp_idx(line_e, 1);
			return ;
		}
		if (line_e->autocomp != 0 && prevkey[0] == '\t' && prevkey[1] == '\0'
			&& line_e->autocomp_list != NULL)
		{
			line_e->autocomp = 2;
			replace_word_from_completion(line_e);
			print_comp_list(line_e, line_e->autocomp_idx);
			return ;
		}
		if (build_list_from_word(line_e) == 0 || line_e->autocomp_size == 1)
		{
			replace_word_from_completion(line_e);
			cancel_autocompletion(line_e);
			return ;
		}
		replace_word(line_e, line_e->autocomp_list->name,
				get_last_common_char(line_e->autocomp_list), NULL);
		line_e->autocomp = 1;
		print_comp_list(line_e, -1);
	}
	else if (is_arrow(key))
	{
		if (line_e->line && key[2] == S_KEY_ARW_LEFT)
		{
			if (line_e->autocomp == 2)
			{
				if (line_e->autocomp_idx > line_e->autocomp_maxrow)
					change_autocomp_idx(line_e, -(line_e->autocomp_maxrow + 1));
			}
			else if (line_e->cursor_pos > 0)
				cursor_move_to(line_e, line_e->cursor_pos - 1);
		}
		else if (line_e->line && key[2] == S_KEY_ARW_RIGHT)
		{
			if (line_e->autocomp == 2)
			{
				if (line_e->autocomp_idx + (line_e->autocomp_maxrow + 1)
					< line_e->autocomp_size)
					change_autocomp_idx(line_e, line_e->autocomp_maxrow + 1);
			}
			else if (line_e->cursor_pos < line_e->len)
				cursor_move_to(line_e, line_e->cursor_pos + 1);
		}
		else if (key[2] == S_KEY_ARW_UP)
		{
			if (line_e->autocomp == 2)
				change_autocomp_idx(line_e, -1);
		}
		else if (key[2] == S_KEY_ARW_DOWN)
		{
			if (line_e->autocomp == 2)
				change_autocomp_idx(line_e, 1);
		}
		return ;
	}
	else if (line_e->line && (key[0] == S_KEY_ERASE && !key[1]))
	{
		if (line_e->line == NULL)
			return ;
		if (line_e->cursor_pos <= 1 && line_e->autocomp > 0)
			cancel_autocompletion(line_e);
		if (line_e->cursor_pos == 0)
			return ;
		if (line_e->autocomp > 0)
			line_e->autocomp = 0;
		line_e->cursor_pos -= 1;
		line_e->len -= 1;
		if (line_e->line[0])
		{
			ft_memmove(line_e->line + (line_e->cursor_pos),\
					line_e->line + (line_e->cursor_pos + 1),\
					line_e->len - line_e->cursor_pos);
		}
		line_e->line[line_e->len] = '\0';
		tputs(tgetstr("cd", NULL), 1, ft_puti);
		ft_putstr_fd("\b \b", STDERR_FILENO);
		ft_putstr_fd(line_e->line + line_e->cursor_pos, STDERR_FILENO);
		cursor_move_from_to(line_e, line_e->len, line_e->cursor_pos);
	}
	// ft_putstr("key too long comming soon - ");
}//in tabptrfct

/*
**  line_edition
**
**  - Called to start the line edition, does not exit until the user
**    presses enter.
*/

int		line_edition(t_edit *line_e)
{
	int 	ret;
	char 	key[MAX_KEY_LEN + 1];
	char 	prevkey[MAX_KEY_LEN + 1];
	struct 	winsize size;
	ioctl(0, TIOCGWINSZ, &size);

	line_e->winsize_col = size.ws_col;
	line_e->winsize_row = size.ws_row;
	line_e->autocomp = 0;
	if (tcsetattr(STDERR_FILENO, TCSADRAIN, line_e->termios) == -1)
		toexit(0, "tcsetattr", 1);
	ft_bzero(prevkey, MAX_KEY_LEN + 1);
	while (1)
	{
	   ft_bzero(key, MAX_KEY_LEN + 1);
	   ret = read(STDIN_FILENO, key, MAX_KEY_LEN);
		if (ret == -1 || ret == 0)
			toexit(line_e, "key:", 1); 
		if (key[0] == S_KEY_ENTER && !key[1])
		{
			if (tcsetattr(STDERR_FILENO, TCSADRAIN, line_e->termiold) == -1)
			   toexit(line_e, "tcsetattr", 1);//maybe just turn off termcap instead of exit
			break ;
		}
		on_key_press(line_e, prevkey, key);
		ft_memcpy(prevkey, key, MAX_KEY_LEN);
	}
	if (line_e->line) //clear everything under the line we just sent
	{
		cursor_end(line_e);
		tputs(tgetstr("cd", NULL), 1, ft_puti);
	}
	ft_file_list_delete(&line_e->autocomp_list);
	ft_putendl("");
	return (1);
}
