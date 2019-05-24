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
	cursor_end(line_e);
	tputs(tgetstr("cd", NULL), 1, ft_puti);
	cursor_actualpos(line_e);
	ft_file_list_delete(&line_e->autocomp_list);
}

/*
**  on_key_press
**
**  - Event handler called whenever the user pressed a key.
**    used to happen input to line or to react to special characters.
*/

void	insert_char(t_edit *line_e, char c)
{
	if (line_e->autocomp == 2)
	{
		line_e->autocomp = 0;
		print_comp_list(line_e, -1);
	}
	if (!(append_to_line(line_e, c)))
		toexit(line_e, "malloc");
	if (line_e->cursor_pos < line_e->len)
		line_e->cursor_pos += 1;
	write(STDERR_FILENO, &c, 1);
	ft_putstr_fd(line_e->line + line_e->cursor_pos, STDERR_FILENO);
	cursor_actualpos(line_e);
}

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

void	on_key_press(t_edit *line_e, char *prevkey, char *key)
{
	if (!key)
	{
		ft_putendl_fd("error : key :null", STDERR_FILENO);
		return ;
	}
	if (ft_strlen(key) <= 1 && ft_isprint(key[0]))
	{
		insert_char(line_e, *key);
		return ;
	}
	else if (ft_strlen(key) == 6 && key[0] == 27 && key[1] == 91 && key[2] == 49 && key[3] == 59 && key[4] == 50 && key[5] == 68)
	{
		//shift + left
	}
	else if (ft_strlen(key) == 6 && key[0] == 27 && key[1] == 91 && key[2] == 49 && key[3] == 59 && key[4] == 50 && key[5] == 67)
	{
		//shift + right
	}
	else if (ft_strlen(key) == 4 && key[0] == 27 && key[1] == 91 && key[2] == 53 && key[3] == 126)
	{
		if (line_e->autocomp == 2)
		{
			if (line_e->autocomp_idx < line_e->winsize_row)
				line_e->autocomp_idx = line_e->autocomp_size;
			else
				line_e->autocomp_idx -= line_e->winsize_row;
			replace_word_from_completion(line_e);
			print_comp_list(line_e, line_e->autocomp_idx);
		}
		else
		{
			cursor_start(line_e);
			line_e->cursor_pos = 0;
		}
	}
	else if (ft_strlen(key) == 4 && key[0] == 27 && key[1] == 91 && key[2] == 54 && key[3] == 126)
	{
		if (line_e->autocomp == 2)
		{
			if (line_e->autocomp_idx + line_e->winsize_row > line_e->autocomp_size)
				line_e->autocomp_idx = 0;
			else
				line_e->autocomp_idx += line_e->winsize_row;
			replace_word_from_completion(line_e);
			print_comp_list(line_e, line_e->autocomp_idx);
		}
		else
		{
			cursor_end(line_e);
			line_e->cursor_pos = line_e->len;
		}
	}
	else if (line_e->autocomp == 2 && ft_strlen(key) == 3 && key[0] == 27 && key[1] == 91 && key[2] == 90) //shift+tab
	{
		if (line_e->autocomp_idx-- == 0)
			line_e->autocomp_idx = line_e->autocomp_size - 1;
		replace_word_from_completion(line_e);
		print_comp_list(line_e, line_e->autocomp_idx);
	}
	else if (ft_strlen(key) <= 1 && key[0] == '\t')
	{
		if (can_insert_tabs(line_e))
		{
			insert_char(line_e, '\t');
			return ;
		}
		if (line_e->line == NULL)
			return ;
		if (line_e->autocomp == 2)
		{
			if (++line_e->autocomp_idx >= line_e->autocomp_size)
				line_e->autocomp_idx = 0;
			replace_word_from_completion(line_e);
			print_comp_list(line_e, line_e->autocomp_idx);
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
				if (line_e->autocomp_idx <= line_e->autocomp_maxrow)
					return ;
				line_e->autocomp_idx -= line_e->autocomp_maxrow + 1;
				replace_word_from_completion(line_e);
				print_comp_list(line_e, line_e->autocomp_idx);
			}
			else if (line_e->cursor_pos > 0)
			{
				line_e->cursor_pos -= 1;
				if (line_e->line[line_e->cursor_pos] == '\n'
					|| (line_e->cursor_pos + line_e->prompt_size + 1) % line_e->winsize_col == 0)
				{
					tputs(tgetstr("up", NULL), 1, ft_puti);
					unsigned int i = 0;
					while (line_e->cursor_pos - i != 0)
					{
						if(line_e->line[line_e->cursor_pos - i] == '\n')
							break ;
						++i;
					}
					while ((i-- + line_e->prompt_size) > 0)
						tputs(tgetstr("nd", NULL), 1, ft_puti);
				}
				else
					tputs(tgetstr("le", NULL), 1, ft_puti); 
			}
		}
		else if (line_e->line && key[2] == S_KEY_ARW_RIGHT)
		{
			if (line_e->autocomp == 2)
			{
				if (line_e->autocomp_idx + (line_e->autocomp_maxrow + 1) >= line_e->autocomp_size)
					return ;
				line_e->autocomp_idx += line_e->autocomp_maxrow + 1;
				replace_word_from_completion(line_e);
				print_comp_list(line_e, line_e->autocomp_idx);
			}
			else if (line_e->cursor_pos < line_e->len)
			{
				line_e->cursor_pos += 1;
				if (line_e->line[line_e->cursor_pos] == '\n'
					|| (line_e->cursor_pos + line_e->prompt_size) % line_e->winsize_col == 0)
				{
					tputs(tgetstr("do", NULL), 1, ft_puti);
					tputs(tgetstr("cr", NULL), 1, ft_puti);
				}
				else
					tputs(tgetstr("nd", NULL), 1, ft_puti);
			}
		}
		else if (key[2] == S_KEY_ARW_UP)
		{
			if (line_e->autocomp == 2)
			{
				if (line_e->autocomp_idx-- == 0)
					line_e->autocomp_idx = line_e->autocomp_size - 1;
				replace_word_from_completion(line_e);
				print_comp_list(line_e, line_e->autocomp_idx);
			}
		}
		else if (key[2] == S_KEY_ARW_DOWN)
		{
			if (line_e->autocomp == 2)
			{
				if (++line_e->autocomp_idx > line_e->autocomp_size)
					line_e->autocomp_idx = 0;
				replace_word_from_completion(line_e);
				print_comp_list(line_e, line_e->autocomp_idx);
			}
		}
		return ;
	}
	else if (line_e->line && (key[0] == S_KEY_ERASE && !key[1]))
	{
		if (line_e->cursor_pos == 0 || line_e->line == NULL)
		{
			cancel_autocompletion(line_e);
			return ;
		}
		if (line_e->autocomp > 0)
		{
			line_e->autocomp = 0;
			print_comp_list(line_e, -1);
		}
		line_e->cursor_pos -= 1;
		line_e->len -= 1;
		if (line_e->line[0])
		{
			ft_memmove(line_e->line + (line_e->cursor_pos),\
					line_e->line + (line_e->cursor_pos + 1),\
					line_e->len - line_e->cursor_pos);
		}
		line_e->line[line_e->len] = '\0';
        tputs(tgetstr("le", NULL), 1, ft_puti);
        write(STDERR_FILENO, " ", 1);
        tputs(tgetstr("le", NULL), 1, ft_puti);
		if (line_e->cursor_pos != line_e->len)
		{
			ft_putstr_fd(line_e->line + line_e->cursor_pos, STDERR_FILENO);
			cursor_reposition(line_e->len - line_e->cursor_pos + 1);
		}
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
		toexit(0, "tcsetattr");
	ft_bzero(prevkey, MAX_KEY_LEN + 1);
	while (1)
	{
	   ft_bzero(key, MAX_KEY_LEN + 1);
	   ret = read(STDIN_FILENO, key, MAX_KEY_LEN);
		if (ret == -1 || ret == 0)
			perror("key:");
		if (key[0] == S_KEY_ENTER && !key[1])
		{
			if (tcsetattr(STDERR_FILENO, TCSADRAIN, line_e->termiold) == -1)
			   toexit(0, "tcsetattr");//maybe just turn off termcap instead of exit
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
