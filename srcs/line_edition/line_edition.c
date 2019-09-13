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
	line_e->autocomp = 0;
	line_e->search_mode = 0;
	cursor_after(line_e);
	tputs(tgetstr("cd", NULL), 1, ft_puti);
	tputs(tgetstr("up", NULL), 1, ft_puti);
	cursor_move_from_to(line_e, line_e->len, line_e->cursor_pos);
	ft_file_list_delete(&line_e->autocomp_list);
}

/*
**  print_line
**
**  - Prints the line correctly, moving the cursor to the left at
**    each encountered newline. Required for proper printing.
*/

void	print_line(t_edit *line_e, unsigned int start)
{
	while (start < line_e->len)
	{
		if (line_e->line[start] == '\t')
			write(STDERR_FILENO, TAB_CHARS, TAB_LEN);
		else
			write(STDERR_FILENO, &line_e->line[start], 1);
		if (line_e->line[start] == '\n')
		{
			tputs(tgetstr("ce", NULL), 1, ft_puti);
			tputs(tgetstr("cr", NULL), 1, ft_puti);
		}
		++start;
	}
	tputs(tgetstr("ce", NULL), 1, ft_puti);
}

/*
**  insert_char
**
**  - Called to insert a character to the line and update it visually.
*/

void	insert_char(t_edit *line_e, char c)
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
	if (get_line_height(line_e, line_e->len) != get_line_height(line_e, line_e->len - 1)
		&& c != '\n')
		ft_nlcr();
	if (line_e->search_mode == 1)
		show_hist_line(line_e);
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

void	go_to_prev_line(t_edit *line_e)
{
    unsigned int i;
    unsigned int x;
    unsigned int curr_height;
    unsigned int height;
    unsigned int newpos;

    if (line_e->line == NULL)
        return ;
    i = 0;
    newpos = 0;
    x = g_shell.prompt_size;
    curr_height = 0;
    height = get_line_height(line_e, line_e->cursor_pos);
    while ((i + 1) < line_e->cursor_pos && curr_height < height)
    {
        ++x;
        if (line_e->line[i++] == '\n' || x >= line_e->winsize_col)
        {
            x = 0;
            if (++curr_height >= height)
            	break ;
            newpos = i;
        }
    }
    cursor_move_to(line_e, newpos);
}

void	go_to_next_line(t_edit *line_e)
{
    unsigned int i;
    unsigned int x;

    if (line_e->line == NULL)
        return ;
    i = 0;
    x = g_shell.prompt_size;
    while (i < line_e->len)
    {
        if (line_e->line[i++] == '\n' || x >= line_e->winsize_col)
        {
            x = 0;
            if (i > line_e->cursor_pos)
            	break ;
        }
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
		else  if (!ft_memcmp(key, "\x1B\x5B\x31\x3B\x32", 5) && line_e->autocomp >= 2)
		{
			if (key[5] == 0x43 || key[5] == 0x42)
				change_autocomp_idx(line_e, line_e->winsize_row);
			else if (key[5] == 0x44 || key[5] == 0x41)
				change_autocomp_idx(line_e, -line_e->winsize_row);
		}
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
	else if (ft_strlen(key) == 1)
	{
		if (*key == 18 && line_e->search_mode != 1)
		{
			cancel_autocompletion(line_e);
			line_e->search_mode = 1;
			show_hist_line(line_e);
		}
	}
}

void	show_hist_line(t_edit *line_e)
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
	cursor_move_from_to2(line_e, ft_strlen("History search: "), str, ft_strlen(str), 0);
	cursor_move_from_to(line_e, line_e->len, line_e->cursor_pos);
	tputs(tgetstr("up", NULL), 1, ft_puti);
}

void	get_hist_line(t_edit *line_e, int offset)
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
			if (line_e->line == NULL)
				return ;
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
			else
				get_hist_line(line_e, 1);
		}
		else if (key[2] == S_KEY_ARW_DOWN)
		{
			if (line_e->autocomp == 2)
				change_autocomp_idx(line_e, 1);
			else
				get_hist_line(line_e, -1);
		}
		return ;
	}
	else if (line_e->line && (key[0] == S_KEY_ERASE && !key[1]))
	{
		if (line_e->line == NULL)
			return ;
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
		cursor_move_to(line_e, line_e->cursor_pos - 1);
		tputs(tgetstr("cd", NULL), 1, ft_puti);
		line_e->len -= 1;
		if (line_e->line[0])
		{
			ft_memmove(line_e->line + (line_e->cursor_pos),\
					line_e->line + (line_e->cursor_pos + 1),\
					line_e->len - line_e->cursor_pos);
		}
		print_line(line_e, line_e->cursor_pos);
		cursor_move_from_to(line_e, line_e->len, line_e->cursor_pos);
		if (line_e->search_mode == 1)
			show_hist_line(line_e);
	}
	// ft_putstr("key too long comming soon - ");
}//in tabptrfct

void	replace_line_with_search(t_edit *line_e)
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
	line_e->history_pos = 0;
	if (tcsetattr(STDERR_FILENO, TCSADRAIN, g_shell.termios) == -1)
		le_exit(0);
	ft_bzero(prevkey, MAX_KEY_LEN + 1);
	while (1)
	{
		ft_bzero(key, MAX_KEY_LEN + 1);
		ret = read(STDIN_FILENO, key, MAX_KEY_LEN);
		if (ret == -1)
			le_exit(0);
		if (key[0] == S_KEY_ENTER && !key[1] && line_e->search_mode == 1)
			replace_line_with_search(line_e);
		else
		{
			if (key[0] == S_KEY_ENTER && !key[1])
			{
				if (tcsetattr(STDERR_FILENO, TCSADRAIN, g_shell.termiold) == -1)
			        le_exit(ER_MALLOC);
				break ;
			}
			on_key_press(line_e, prevkey, key);
			ft_memcpy(prevkey, key, MAX_KEY_LEN);
		}
	}
	if (line_e->line) 
		cursor_after(line_e);
	else
		ft_nlcr();
	tputs(tgetstr("cd", NULL), 1, ft_puti);
	ft_file_list_delete(&line_e->autocomp_list);
	return (1);
}
