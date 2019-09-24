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
	return (c == '\n' || c == ';' || c == '&');
}


int		is_whitespace(char c)
{
	return (c == '\t' || c == ' ');
}

void	remove_duplicate_whitespaces(t_edit *line_e)
{
	unsigned int	i;
	bool			escape;
	int				count;
	int				whitespace_count;

	i = -1;
	escape = 0;
	count = 1;
	whitespace_count = 1;
	while (++i < line_e->len && line_e->line[i])
	{
		if (escape)
		{
			count = 0;
			whitespace_count = 0;
			escape = 0;
			continue ;
		}
		if (line_e->line[i] == '\\')
		{
			escape = 1;
			continue ;
		}
		if (line_e->line[i] == '\'' || line_e->line[i] == '"')
		{
			quote_match(line_e->line, &i, line_e->len, line_e->line[i]);
			count = 0;
			whitespace_count = 0;
			continue ;
		}
		if (is_command_separator(line_e->line[i]))
			++count;
		else if (is_whitespace(line_e->line[i]))
			++whitespace_count;
		else
		{
			count = 0;
			whitespace_count = 0;
		}
		if (count == 2 || whitespace_count == 2)
		{
			ft_strcpy(line_e->line + i, line_e->line + i + 1);
			line_e->len -= 1;
			if (count == 2)
			{
				count = 1;
				whitespace_count = 0;
			}
			else
			{
				count = 0;
				whitespace_count = 1;
			}
			--i;
			continue ;
		}
	}
	if (is_whitespace(line_e->line[0]) || is_command_separator(line_e->line[0]))
		ft_strcpy(line_e->line, line_e->line + 1);
	if (i > 0 && (is_command_separator(line_e->line[i - 1])
		|| is_whitespace(line_e->line[i - 1])) && line_e->line[i - 1] != '&')
		line_e->line[i - 1] = '\0';
}
