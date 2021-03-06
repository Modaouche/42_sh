/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirect_great.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 17:21:36 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 09:00:48 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	token_isgreat(t_token *actual_token, char *line, unsigned int *i)
{
	actual_token->tokind = T_GREAT;
	actual_token->lexeme = ft_strdup(">");
	++(*i);
	if (line[*i] == '>')
		token_isdgreat(actual_token, i);
	if (line[*i] == '|')
		token_isclobber(actual_token, i);
	if (line[*i] == '&')
		token_isgreatand(actual_token, i);
}

void	token_isdgreat(t_token *actual_token, unsigned int *i)
{
	actual_token->tokind = T_DGREAT;
	actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, ">", 1);
	++(*i);
}

void	token_isclobber(t_token *actual_token, unsigned int *i)
{
	actual_token->tokind = T_CLOBBER;
	actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, "|", 1);
	++(*i);
}

void	token_isgreatand(t_token *actual_token, unsigned int *i)
{
	actual_token->tokind = T_GREATAND;
	actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, "&", 1);
	++(*i);
}
