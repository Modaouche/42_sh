/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 08:36:30 by araout            #+#    #+#             */
/*   Updated: 2019/09/23 08:50:20 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	dollars_cmd(const char *line, char **word, unsigned int *i)
{
	++(*i);
	if (line[*i] == '$')
		*word = (!*word) ? ft_itoa(g_shell.pid)
			: ft_strjoin_free(*word, ft_itoa(g_shell.pid), 3);
	else if (line[*i] == '{')
		expand_brackets(line, word, i);
	else if (line[*i] == '(')
		ft_putstr_fd("./21sh error\"(\" not supported", STDERR_FILENO);
	else if (line[*i] == '?')
		*word = (!*word) ? ft_itoa(g_shell.ret)
			: ft_strjoin_free(*word, ft_itoa(g_shell.ret), 3);
	else if (line[*i] == '\\' || line[*i] == ' '\
			|| line[*i] == '\t' || !line[*i])
		*word = (!*word) ? ft_strdup("$") : ft_strjoin_free(*word, "$", 1);
	else if (ft_isalnum(line[*i]))
		insert_env_var_value(line, word, i);
}
