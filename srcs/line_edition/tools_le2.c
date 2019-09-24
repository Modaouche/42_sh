/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_le2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kicausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 00:22:16 by kicausse          #+#    #+#             */
/*   Updated: 2019/09/25 00:22:17 by kicausse         ###   ########.fr       */
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
