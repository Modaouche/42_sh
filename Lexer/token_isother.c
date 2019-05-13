/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_isother.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 19:17:05 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/11 14:29:34 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"


void    token_iseof(t_token *actual_token, const char *line, int *i)
{
    (void)line;
    (void)i;
    actual_token->tokind = T_EOF;
}

void    token_isnewl(t_token *actual_token, const char *line, int *i)
{
    (void)line;
    actual_token->tokind = T_NEWL;
    actual_token->lexeme = ft_strdup("\n");
    ++(*i);
}

void    token_isbang(t_token *actual_token, const char *line, int *i)
{
    (void)line;
    actual_token->tokind = T_BANG;
    actual_token->lexeme = ft_strdup("!");
    ++(*i);
}

void    token_issemi(t_token *actual_token, const char *line, int *i)
{
    (void)line;
    actual_token->tokind = T_SEMI;
    actual_token->lexeme = ft_strdup(";");
    ++(*i);
}