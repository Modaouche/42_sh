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


void	replace_word_with_alias(t_edit *line_e, char *alias, char *value);

void 	replace_aliases(t_edit *line_e)
{
	unsigned int i;
	int x;

	if (!g_shell.aliasp)
		return ;
	i = 0;
	while (g_shell.aliasp[i])
	{
		if ((x = ft_cfind(g_shell.aliasp[i], '=')) != -1)
		{
			g_shell.aliasp[i][x] = '\0';
			replace_word_with_alias(line_e, g_shell.aliasp[i], &g_shell.aliasp[i][x + 1]);
			g_shell.aliasp[i][x] = '=';
		}
		++i;
	}
}

void	replace_word_with_alias(t_edit *line_e, char *alias, char *value)
{
	unsigned int	i;
	unsigned int	escape;
	unsigned int	can_replace;
	char			*tmp;
	int				alias_length;

	can_replace = 1;
	i = 0;
	escape = 0;
	alias_length = ft_strlen(alias);
	while (line_e->line[i])
	{
		while (is_separator(line_e->line[i]))
		{
			if (line_e->line[i] == ';' || line_e->line[i] == '\n')
				can_replace = 1;
			++i;
		}
		if (escape)
		{
			escape = 0;
			++i;
			continue ;
		}
		if (line_e->line[i] == '\\')
		{
			escape = 1;
			++i;
			continue ;
		}
		if (line_e->line[i] == '"' || line_e->line[i] == '\'')
			quote_match(line_e->line, &i, ft_strlen(line_e->line), line_e->line[i]);
		else if (ft_strncmp(&line_e->line[i], alias, alias_length) == 0 && can_replace
				&& (is_separator(line_e->line[i + alias_length]) || line_e->line[i + alias_length] == '\0'))
		{
			ft_strcut(&line_e->line[i], 0, alias_length);
			tmp = line_e->line;
			line_e->line = ft_strins_malloc(tmp, value, i);
			ft_strdel(&tmp);
		}
		while (!is_separator(line_e->line[i]) && line_e->line[i] != '\0')
			++i;
		can_replace = 0;
	}
}