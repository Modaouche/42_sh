/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 21:31:42 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/23 09:39:22 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

//norme + unleaks + protection malloc

int    backslash(const char *line, char **word, unsigned int *i, int qt)
{
	(void)qt;
	++(*i);
	if (!line[*i])
	{
		*i = 0;
		return (0);
	}
	else if (line[*i] == '\n')
		++(*i);
	else if (ft_strchr(BKSH_DQT_CMP, line[*i]))
		*word = (!*word) ? ft_strndup(line + *i, 1)
			: ft_strjoin_free(*word, ft_strndup(line + *i, 1), 3);
	else if (ft_isspace_inhib(line[*i]))
		*word = (!*word) ? ft_strndup(line + *i, 1)
			: ft_strjoin_free(*word, ft_strndup(line + *i, 1), 3);
	else
		--(*i);
	return (1);
}

int    backslash_end(t_edit *line_e, unsigned int *i, int *ret)
{
	init_line(line_e);
	g_shell.prompt_size = print_prompt(7);
	line_edition(line_e);
	if (!line_e->line)
		line_e->line = ft_memalloc(1);
	if (for_end_word_inhib(line_e->line[0]))
	{
		*i = 0;
		*ret = 0;
		return (0);
	}
	return (1);
}

void    dollars_cmd(const char *line, char **word, unsigned int *i)
{
	++(*i);
	if (line[*i] == '$')
		*word = (!*word) ? ft_itoa(g_shell.pid)
			: ft_strjoin_free(*word, ft_itoa(g_shell.pid), 3);
	else if (line[*i] == '?')
		*word = (!*word) ? ft_itoa(g_shell.ret)
			: ft_strjoin_free(*word, ft_itoa(g_shell.ret), 3);
	else if (line[*i] == '(')
		ft_putstr("~[  $(  ]~\n");//substition(word, line[*i], i);//to creat
	else if (line[*i] == '{')
		ft_putstr("~[  ${  ]~\n");//word_expansion(word, line[*i], i);//to creat
	else if (line[*i] == '\\' || line[*i] == ' '\
			|| line[*i] == '\t' || !line[*i])
		*word = (!*word) ? ft_strdup("$") : ft_strjoin_free(*word, "$", 1);
	else if (ft_isalnum(line[*i]))
		ft_putstr("~[  $VAR  ]~\n");//get_varenv();//to creat
}
