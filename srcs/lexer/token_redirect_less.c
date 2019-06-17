/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirect_less.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 17:21:36 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 01:38:50 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void    token_isless(t_token *actual_token, char *line, unsigned int *i)
{
    actual_token->tokind = T_LESS;
    actual_token->lexeme = ft_strdup("<");
    ++(*i);
    if (line[*i] == '<')
        token_isdless(actual_token, line, i);
    if (line[*i] == '>')
        token_islessgreat(actual_token, i);
    if (line[*i] == '&')
        token_islessand(actual_token, i);
}

void    token_isdless(t_token *actual_token, char *line, unsigned int *i)
{
    actual_token->tokind = T_DLESS;
    actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, "<", 1);
    ++(*i);
    if (line[*i] == '-')
        token_isdlessdash(actual_token, i);
}

void    token_isdlessdash(t_token *actual_token, unsigned int *i)
{
    actual_token->tokind = T_DLESSDASH;
    actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, "-", 1);
    ++(*i);
}

void    token_islessgreat(t_token *actual_token, unsigned int *i)
{
    actual_token->tokind = T_LESSGREAT;
    actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, ">", 1);
    ++(*i);
}

void    token_islessand(t_token *actual_token, unsigned int *i)
{
    actual_token->tokind = T_LESSAND;
    actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, "&", 1);
    ++(*i);
}
