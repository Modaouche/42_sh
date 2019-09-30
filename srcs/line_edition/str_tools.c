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
