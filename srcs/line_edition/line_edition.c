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

void		print_line(t_edit *line_e, unsigned int start)
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

void		change_autocomp_idx(t_edit *line_e, int value)
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

int			handle_hey(t_edit *line_e, char *key, char *prevkey)
{
	ft_bzero(key, MAX_KEY_LEN + 1);
	if (read(STDIN_FILENO, key, MAX_KEY_LEN) == -1)
		le_exit(0);
	if (key[0] == S_KEY_CTRL_D && key[1] == 0 && line_e->len == 0)
		fexit(0);
	if (key[0] == S_KEY_ENTER && !key[1] && line_e->search_mode == 1)
		replace_line_with_search(line_e);
	else
	{
		if (key[0] == S_KEY_ENTER && !key[1])
		{
			if (tcsetattr(STDERR_FILENO, TCSADRAIN, g_shell.termiold) == -1)
				le_exit(ER_MALLOC);
			return (0);
		}
		on_key_press(line_e, prevkey, key);
		ft_memcpy(prevkey, key, MAX_KEY_LEN);
	}
	return (1);
}

int			line_edition(t_edit *line_e)
{
	char			key[MAX_KEY_LEN + 1];
	char			prevkey[MAX_KEY_LEN + 1];
	struct winsize	size;

	ioctl(0, TIOCGWINSZ, &size);
	line_e->winsize_col = size.ws_col;
	line_e->winsize_row = size.ws_row;
	line_e->autocomp = 0;
	line_e->history_pos = 0;
	if (tcsetattr(STDERR_FILENO, TCSADRAIN, g_shell.termios) == -1)
		le_exit(0);
	ft_bzero(prevkey, MAX_KEY_LEN + 1);
	while (handle_hey(line_e, key, prevkey))
		;
	if (line_e->line)
		cursor_after(line_e);
	else
		ft_nlcr();
	tputs(tgetstr("cd", NULL), 1, ft_puti);
	ft_file_list_delete(&line_e->autocomp_list);
	return (1);
}
