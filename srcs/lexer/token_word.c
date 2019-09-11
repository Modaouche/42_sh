/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 17:38:23 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/22 17:25:49 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void    token_isword(t_token *actual_token, char *line, unsigned int *i)
{
	unsigned int i2;

	i2 = *i;
	skip_predicat(&line, &i2, &ft_isdigit);
	if (line[i2] == '<' || line[i2] == '>')
		token_isio_nb(actual_token, line, i);
	else if (!token_isassignmt(actual_token, line, i))
	{
		actual_token->tokind = T_WORD;
		actual_token->lexeme = get_word(i);
	}
}

void    token_isio_nb(t_token *actual_token, char *line, unsigned int *i)
{
	unsigned int len;

	len = *i;
	skip_predicat(&line, &len, &ft_isdigit);
	actual_token->tokind = T_IO_NB;
	actual_token->lexeme = ft_strndup(line + *i, len - *i);
	skip_predicat(&line, i, &ft_isdigit);
}

int    isassign(int c)
{
	return ((ft_isalnum(c) || c == '_'));
}

static bool	is_arg_cmd(void)
{
	if (last_token(0) == T_WORD)
		return (true);
	return (false);		
}

unsigned int	token_isassignmt(t_token *actual_token, char *line, unsigned int *i)
{
	unsigned int len;

	len = *i;
	if (ft_isdigit(line[len]) || line[len] == '=')
		return (0);
	skip_predicat(&line, &len, &isassign);
	if (line[len] != '=' || (line[len] == '=' && is_arg_cmd())) 
		return (0);
	len++;
	actual_token->tokind = T_ASGMT_WRD;
	actual_token->lexeme = ft_strndup(line + *i, len - *i);
	actual_token->lexeme = ft_strjoin(actual_token->lexeme, get_word(&len));
	*i = len;
	return (1);
}
