/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 11:16:46 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 09:21:07 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_command_separator(char c)
{
	return (c == '\n' || c == ';');
}

int		is_whitespace(char c)
{
	return (c == '\t' || c == ' ');
}

void	remove_extra_seps(t_edit *line_e, t_dup_wspc *wp)
{
	if (is_command_separator(line_e->line[wp->i]))
		++wp->count;
	else if (is_whitespace(line_e->line[wp->i]))
		++wp->whitespace_count;
	else
	{
		wp->count = 0;
		wp->whitespace_count = 0;
	}
	if (wp->count == 2 || wp->whitespace_count == 2)
	{
		ft_strcpy(line_e->line + wp->i, line_e->line + wp->i + 1);
		line_e->len -= 1;
		wp->whitespace_count = (wp->count != 2);
		wp->count = (wp->count == 2);
		--wp->i;
	}
}

void	remove_suffix_seps(t_edit *line_e)
{
	if (is_whitespace(line_e->line[0]) || is_command_separator(line_e->line[0]))
		ft_strcpy(line_e->line, line_e->line + 1);
}

void	remove_duplicate_whitespaces(t_edit *line_e)
{
	t_dup_wspc wp;

	wp.i = -1;
	wp.escape = 0;
	wp.count = 1;
	wp.whitespace_count = 1;
	while (++wp.i < line_e->len && line_e->line[wp.i])
	{
		if (wp.escape || line_e->line[wp.i] == '\\')
		{
			wp.escape = !wp.escape;
			if (line_e->line[wp.i] == '\\')
				ft_bzero(&(wp.count), 8);
			continue ;
		}
		if (line_e->line[wp.i] == '\'' || line_e->line[wp.i] == '"')
		{
			quote_match(line_e->line, &wp.i, line_e->len, line_e->line[wp.i]);
			ft_bzero(&(wp.count), 8);
			continue ;
		}
		remove_extra_seps(line_e, &wp);
	}
	remove_suffix_seps(line_e);
}
