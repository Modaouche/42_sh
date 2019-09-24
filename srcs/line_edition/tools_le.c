/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_le.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 11:00:19 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 02:28:51 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			is_arrow(char *key)
{
	return ((key[0] == 27 && key[1] == 91 && (key[2] >= 65) && key[2] <= 68)\
	? key[2] : 0);
}

void		ft_nlcr(void)
{
	tputs(tgetstr("do", NULL), 1, ft_puti);
	tputs(tgetstr("cr", NULL), 1, ft_puti);
}

uint		get_line_height(t_edit *line_e, unsigned int end)
{
	unsigned int i;
	unsigned int x;
	unsigned int height;

	if (line_e->line == NULL)
		return (1);
	i = 0;
	x = g_shell.prompt_size;
	height = 1;
	while (i < end && line_e->line[i])
	{
		++x;
		if (line_e->line[i] == '\t')
			x += TAB_LEN - 1;
		if (line_e->line[i++] == '\n' || x >= line_e->winsize_col)
		{
			x = 0;
			++height;
		}
	}
	return (height);
}

uint		get_str_height(t_edit *line_e, unsigned int x,
			char *str, unsigned int end)
{
	unsigned int i;
	unsigned int height;

	if (str == NULL)
		return (1);
	i = 0;
	height = 1;
	while (i < end && str[i])
	{
		++x;
		if (str[i] == '\t')
			x += TAB_LEN - 1;
		if (str[i++] == '\n' || x >= line_e->winsize_col)
		{
			x = 0;
			++height;
		}
	}
	return (height);
}

uint		get_index_x_pos(t_edit *line_e, unsigned int pos)
{
	unsigned int i;
	unsigned int x;
	unsigned int n;

	if (line_e->line == NULL)
		return (g_shell.prompt_size);
	i = 0;
	x = g_shell.prompt_size;
	n = 0;
	while (i < pos && line_e->line[i])
	{
		if (line_e->line[i] == '\t')
			x += TAB_LEN - 1;
		if (x++ >= line_e->winsize_col)
			++n;
		if (line_e->line[i++] == '\n' || x >= line_e->winsize_col)
			x = 0;
	}
	return (x + n);
}

uint		get_str_index_x_pos(t_edit *line_e, unsigned int x,
			char *str, unsigned int pos)
{
	unsigned int i;
	unsigned int n;

	if (line_e->line == NULL)
		return (x);
	i = 0;
	n = 0;
	while (i < pos && str[i])
	{
		if (str[i] == '\t')
			x += TAB_LEN - 1;
		if (x++ >= line_e->winsize_col)
			++n;
		if (str[i++] == '\n' || x >= line_e->winsize_col)
			x = 0;
	}
	return (x + n);
}

size_t		print_prompt(unsigned int btn)
{
	char	*prompt;
	size_t	len;
	char	*currpath;
	size_t	offset;

	offset = 0;
	if ((currpath = getcwd(NULL, 1023)) == NULL)
		currpath = "Unknown path";
	if (btn == 0)
	{
		prompt = ft_multijoin(5, "\033[38;5;6m42sh\033[0m (", currpath, ") ",
			g_shell.ret == 0 ? "\033[38;5;10m" : "\033[38;5;09m", "$>\033[0m ");
		offset = 27;
	}
	else if (btn == 1)
		prompt = ft_strdup("pipe $> ");
	else if (btn == 2)
		prompt = ft_strdup("cmdor $> ");
	else if (btn == 3)
		prompt = ft_strdup("cmdand $> ");
	else if (btn == 4)
		prompt = ft_strdup("quote $> ");
	else if (btn == 5)
		prompt = ft_strdup("dquote $> ");
	else if (btn == 6)
		prompt = ft_strdup("heredoc $> ");
	else if (btn == 7)
		prompt = ft_strdup("$> ");
	len = ft_strlen(prompt) - offset;
	ft_putstr(prompt);
	ft_strdel(&prompt);
	return (len);
}

int			ft_puti(int i)
{
	return (write(STDERR_FILENO, &i, 1));
}
