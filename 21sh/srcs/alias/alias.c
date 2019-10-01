/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 11:16:46 by modaouch          #+#    #+#             */
/*   Updated: 2019/07/16 04:23:05 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

void	replace_aliases(t_edit *line_e)
{
	unsigned int	i;
	int				x;

	if (!g_shell.aliasp)
		return ;
	i = 0;
	while (g_shell.aliasp[i])
	{
		if ((x = ft_cfind(g_shell.aliasp[i], '=')) != -1)
		{
			g_shell.aliasp[i][x] = '\0';
			replace_word_with_alias(line_e, g_shell.aliasp[i],
				&g_shell.aliasp[i][x + 1]);
			g_shell.aliasp[i][x] = '=';
		}
		++i;
	}
}

void	skip_initial_separators(t_edit *line_e, t_alias *al)
{
	while (is_separator(line_e->line[al->i]))
	{
		if (line_e->line[al->i] == ';' || line_e->line[al->i] == '\n')
			al->can_replace = 1;
		++al->i;
	}
}

void	get_to_next_separator(t_edit *line_e, t_alias *al)
{
	while (!is_separator(line_e->line[al->i]) && line_e->line[al->i] != '\0'
		&& line_e->line[al->i] != '\'')
		++al->i;
	al->can_replace = 0;
}

int		skip_quotes_and_replace(t_edit *line_e, t_alias *al,
		char *alias, char *value)
{
	if (line_e->line[al->i] == '"' || line_e->line[al->i] == '\'')
		quote_match(line_e->line, &al->i, ft_strlen(line_e->line),
					line_e->line[al->i]);
	else if (ft_strncmp(&line_e->line[al->i], alias, al->alias_length) == 0
			&& al->can_replace
			&& (is_separator(line_e->line[al->i + al->alias_length])
			|| line_e->line[al->i + al->alias_length] == '\0'))
	{
		ft_strcut(&line_e->line[al->i], 0, al->alias_length);
		al->tmp = line_e->line;
		line_e->line = ft_strins_malloc(al->tmp, value, al->i);
		ft_strdel(&al->tmp);
		return (1);
	}
	return (0);
}

void	replace_word_with_alias(t_edit *line_e, char *alias, char *value)
{
	t_alias	al;

	al.can_replace = 1;
	al.i = 0;
	al.escape = 0;
	al.alias_length = ft_strlen(alias);
	while (line_e->line[al.i])
	{
		if (al.escape)
		{
			al.escape = 0;
			++al.i;
			continue ;
		}
		skip_initial_separators(line_e, &al);
		if (line_e->line[al.i] == '\\')
		{
			al.escape = 1;
			++al.i;
			continue ;
		}
		if (skip_quotes_and_replace(line_e, &al, alias, value))
			al.can_replace = 0;
		get_to_next_separator(line_e, &al);
	}
}
