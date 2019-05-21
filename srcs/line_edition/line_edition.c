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
**  str_add
**
**  - Adds a character to the input line, and if necessary, reallocates the
**  line to fit it's new size.
*/

int		str_add(t_edit *line_e, const char to_add)
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
**  - Hides and free the current autocompletion
*/

void	cancel_autocompletion(t_edit *line_e)
{
	line_e->autocompletion = 0;
	cursor_end(line_e);
	tputs(tgetstr("cd", NULL), 1, ft_puti);
	cursor_actualpos(line_e);
	ft_file_list_delete(&line_e->autocompletion_list);
}

/*
**  putkey_in_line
**
**  - Event handler called whenever the user pressed a key.
**  used to happen input to line or to react to special characters.
*/

void	putkey_in_line(t_edit *line_e, char *prevkey, char *key)
{
	if (!key)
	{
		ft_putendl_fd("error : key :null", STDERR_FILENO);
		return ;
	}
	if (ft_strlen(key) <= 1 && ft_isprint(key[0]))
	{
		if (line_e->autocompletion == 2)
			line_e->autocompletion = 1;
		if (!(str_add(line_e, *key)))
			toexit(line_e, "malloc");
		if (line_e->cursor_pos <= line_e->len)
			line_e->cursor_pos += 1;
		write(STDERR_FILENO, key, 1);
		ft_putstr_fd(line_e->line + line_e->cursor_pos, STDERR_FILENO);
		cursor_reposition(line_e->len - line_e->cursor_pos);
		return ;
	}
	else if (line_e->autocompletion == 2 && ft_strlen(key) == 3 && key[0] == 27 && key[1] == 91 && key[2] == 90) //shift+tab
	{
		if (line_e->autocompletion_idx == 0)
			line_e->autocompletion_idx = line_e->autocompletion_size - 1;
		else
			--line_e->autocompletion_idx;
		if (ft_file_list_at(line_e->autocompletion_list, line_e->autocompletion_idx))
			replace_word(line_e, ft_file_list_at(line_e->autocompletion_list, line_e->autocompletion_idx)->name);
		print_autocompletion_list(line_e, line_e->autocompletion_idx);
	}
	else if (ft_strlen(key) <= 1 && key[0] == '\t' && line_e->line)
	{
		if (line_e->autocompletion == 2)
		{
			if (++line_e->autocompletion_idx >= line_e->autocompletion_size)
				line_e->autocompletion_idx = 0;
			if (ft_file_list_at(line_e->autocompletion_list, line_e->autocompletion_idx))
				replace_word(line_e, ft_file_list_at(line_e->autocompletion_list, line_e->autocompletion_idx)->name);
			print_autocompletion_list(line_e, line_e->autocompletion_idx);
			return ;
		}
		if (line_e->autocompletion != 0 && prevkey[0] == '\t' && prevkey[1] == '\0'
			&& line_e->autocompletion_list != NULL)
		{
			//autocompletion arrow mode
			line_e->autocompletion = 2;
			line_e->autocompletion_idx = 0;
			replace_word(line_e, line_e->autocompletion_list->name);
			print_autocompletion_list(line_e, line_e->autocompletion_idx);
			return ;
		}
		if (complete_from_word(line_e) == 0)
		{
			cursor_end(line_e);
			tputs(tgetstr("cd", NULL), 1, ft_puti);
			cursor_actualpos(line_e);
			return ;
		}
		if (line_e->autocompletion_list == NULL)
		{
			cancel_autocompletion(line_e);
			return ;
		}
		if (line_e->autocompletion_size == 1)
		{
			if (line_e->autocompletion_list->type == 4)
			{
				char *tmp = ft_strjoin(line_e->autocompletion_list->name, "/");
				replace_word(line_e, tmp);
				ft_strdel(&tmp);
			}
			else
				replace_word(line_e, line_e->autocompletion_list->name);
			cancel_autocompletion(line_e);
			return ;
		}
		else if (line_e->autocompletion_size > 1)
		{
			char *tmp = ft_strsub(line_e->autocompletion_list->name,
				0, get_last_common_char(line_e->autocompletion_list));
			replace_word(line_e, tmp);
			free(tmp);
		}
		line_e->autocompletion = 1;
		print_autocompletion_list(line_e, -1);
	}
	else if (is_arrow(key))
	{
		if (line_e->line && key[2] == S_KEY_ARW_LEFT)
		{
			if (line_e->autocompletion == 2)
			{
				if (line_e->autocompletion_idx <= line_e->autocompletion_maxrow)
					;
				else
					line_e->autocompletion_idx -= line_e->autocompletion_maxrow + 1;
				if (ft_file_list_at(line_e->autocompletion_list, line_e->autocompletion_idx))
					replace_word(line_e, ft_file_list_at(line_e->autocompletion_list, line_e->autocompletion_idx)->name);
				print_autocompletion_list(line_e, line_e->autocompletion_idx);
			}
			else if (line_e->cursor_pos > 0)
			{
				struct winsize size;
				ioctl(0, TIOCGWINSZ, &size);
				line_e->cursor_pos -= 1;
				if (line_e->line[line_e->cursor_pos] == '\n'
					|| (line_e->cursor_pos + line_e->prompt_size + 1) % size.ws_col == 0)
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
			if (line_e->autocompletion == 2)
			{
				if (line_e->autocompletion_idx + (line_e->autocompletion_maxrow + 1) >= line_e->autocompletion_size)
					;
				else
					line_e->autocompletion_idx += line_e->autocompletion_maxrow + 1;
				if (ft_file_list_at(line_e->autocompletion_list, line_e->autocompletion_idx))
					replace_word(line_e, ft_file_list_at(line_e->autocompletion_list, line_e->autocompletion_idx)->name);
				print_autocompletion_list(line_e, line_e->autocompletion_idx);
			}
			else if (line_e->cursor_pos < line_e->len)
			{
				struct winsize size;
				ioctl(0, TIOCGWINSZ, &size);
				line_e->cursor_pos += 1;
				if (line_e->line[line_e->cursor_pos] == '\n'
					|| (line_e->cursor_pos + line_e->prompt_size) % size.ws_col == 0)
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
			if (line_e->autocompletion == 2)
			{
				if (line_e->autocompletion_idx-- == 0)
					line_e->autocompletion_idx = line_e->autocompletion_size - 1;
				if (ft_file_list_at(line_e->autocompletion_list, line_e->autocompletion_idx))
					replace_word(line_e, ft_file_list_at(line_e->autocompletion_list, line_e->autocompletion_idx)->name);
				print_autocompletion_list(line_e, line_e->autocompletion_idx);
			}
		}
		else if (key[2] == S_KEY_ARW_DOWN)
		{
			if (line_e->autocompletion == 2)
			{
				if (++line_e->autocompletion_idx > line_e->autocompletion_size)
					line_e->autocompletion_idx = 0;
				if (ft_file_list_at(line_e->autocompletion_list, line_e->autocompletion_idx))
					replace_word(line_e, ft_file_list_at(line_e->autocompletion_list, line_e->autocompletion_idx)->name);
				print_autocompletion_list(line_e, line_e->autocompletion_idx);
			}
		}
		return ;
	}
	else if (line_e->cursor_pos && line_e->line && (key[0] == S_KEY_ERASE && !key[1]))
	{
		line_e->cursor_pos -= 1;
		line_e->len -= 1;
		if (line_e->line[0])
		{
			ft_memmove(line_e->line + (line_e->cursor_pos),\
					line_e->line + (line_e->cursor_pos + 1),\
					line_e->len - line_e->cursor_pos);
		}
		line_e->line[line_e->len] = '\0';
		write(STDERR_FILENO, "\b \b", 3);
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
**  pressed enter.
*/

int		line_edition(t_edit *line_e)
{
	int ret;
	char key[MAX_KEY_LEN];
	char prevkey[MAX_KEY_LEN];

	line_e->autocompletion = 0;
	if (tcsetattr(STDERR_FILENO, TCSADRAIN, line_e->termios) == -1)
		toexit(0, "tcsetattr");
	ft_bzero(prevkey, MAX_KEY_LEN);
	while (1)
	{
	   ft_bzero(key, MAX_KEY_LEN);
	   ret = read(STDIN_FILENO, key, MAX_KEY_LEN);
		if (ret == -1 || ret == 0)
			perror("key:");
		if (key[0] == S_KEY_ENTER && !key[1])
		{
			if (tcsetattr(STDERR_FILENO, TCSADRAIN, line_e->termiold) == -1)
			   toexit(0, "tcsetattr");//maybe just turn off termcap instead of exit
			break ;
		}
		putkey_in_line(line_e, prevkey, key);
		ft_memcpy(prevkey, key, MAX_KEY_LEN);
	}
	if (line_e->line) //clear everything under the line we just sent
	{
		cursor_end(line_e);
		tputs(tgetstr("cd", NULL), 1, ft_puti);
	}
	ft_file_list_delete(&line_e->autocompletion_list);
	ft_putendl("");
	return (1);
}