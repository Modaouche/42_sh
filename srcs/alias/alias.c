/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 11:16:46 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 08:08:45 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
			replace_word_with_alias(line_e, g_shell.aliasp[i],\
					&g_shell.aliasp[i][x + 1]);
			g_shell.aliasp[i][x] = '=';
		}
		++i;
	}
}

void	loop_alias_rep(t_edit *line_e, char *alias, t_alias *a, char *value)
{
	if (line_e->line[a->i] == '"' || line_e->line[a->i] == '\'')
		quote_match(line_e->line, &(a->i), ft_strlen(line_e->line),\
				line_e->line[a->i]);
	else if (ft_strncmp(&line_e->line[a->i], alias, a->alias_length) == 0 \
			&& a->can_replace\
			&& (is_separator(line_e->line[a->i + a->alias_length])\
			|| line_e->line[a->i + a->alias_length] == '\0'))
	{
		ft_strcut(&line_e->line[a->i], 0, a->alias_length);
		a->tmp = line_e->line;
		line_e->line = ft_strins_malloc(a->tmp, value, a->i);
		ft_strdel(&(a->tmp));
	}
	while (!is_separator(line_e->line[a->i]) && line_e->line[a->i] != '\0')
		a->i++;
}

void	replace_word_with_alias(t_edit *line_e, char *alias, char *value)
{
	t_alias			a;

	a.can_replace = 1;
	a.i = 0;
	a.escape = 0;
	a.alias_length = ft_strlen(alias);
	while (line_e->line[a.i])
	{
		while (is_separator(line_e->line[a.i]))
		{
			if (line_e->line[a.i] == ';' || line_e->line[a.i] == '\n')
				a.can_replace = 1;
			a.i++;
		}
		if (a.escape && ((a.escape = 0) == 0))
			a.i++;
		if (line_e->line[a.i] == '\\')
		{
			a.escape = 1;
			a.i++;
			continue ;
		}
		loop_alias_rep(line_e, alias, &a, value);
		a.can_replace = 0;
	}
}
