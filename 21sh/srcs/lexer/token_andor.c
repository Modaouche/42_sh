/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_andor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 17:38:16 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 08:59:26 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	token_isamper(t_token *actual_token, char *line, unsigned int *i)
{
	actual_token->tokind = T_AMPER;
	actual_token->lexeme = ft_strdup("&");
	++(*i);
	if (line[*i] == '&')
		token_isand(actual_token, i);
}

void	token_isand(t_token *actual_token, unsigned int *i)
{
	actual_token->tokind = T_AND_IF;
	actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, "&", 1);
	++(*i);
}

void	token_ispipe(t_token *actual_token, char *line, unsigned int *i)
{
	actual_token->tokind = T_PIPE;
	actual_token->lexeme = ft_strdup("|");
	++(*i);
	if (line[*i] == '|')
		token_isor(actual_token, i);
}

void	token_isor(t_token *actual_token, unsigned int *i)
{
	actual_token->tokind = T_OR_IF;
	actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, "|", 1);
	++(*i);
}
