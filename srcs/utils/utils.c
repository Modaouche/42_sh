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

void	remove_duplicate_whitespaces(t_edit *line_e)
{
	unsigned int	i;
	bool			escape;
	int				count;

	i = -1;
	escape = 0;
	count = 1;
	while (++i < line_e->len && line_e->line[i])
	{
		if (escape)
		{
			count = 0;
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
			continue ;
		}
		if (is_command_separator(line_e->line[i]))
			++count;
		else
			count = 0;
		if (count == 2)
		{
			ft_strcpy(line_e->line + i, line_e->line + i + 1);
			line_e->len -= 1;
			count = 1;
			--i;
			continue ;
		}
	}
	if (i > 0 && is_command_separator(line_e->line[i - 1]))
		line_e->line[i - 1] = '\0';
}
