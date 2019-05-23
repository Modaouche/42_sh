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

#include "../includes/shell.h"

void    token_isword(t_token *actual_token, const char *line, unsigned int *i)
{
    char *word;

    if (ft_isdigit(line[*i]) && (line[*i + 1] == '<' || line[*i + 1] == '>'))// peut etre to change into word ou bien ajouter une condition pour getword
        token_isio_nb(actual_token, line, i);
    else
    {
        word = get_word(i);
        actual_token->tokind = T_WORD;
        actual_token->lexeme = word;
        //skip_predicat(&line, i, &ft_isword);//check le isword
    }
}

void    token_isio_nb(t_token *actual_token, const char *line, unsigned int *i)
{
    actual_token->tokind = T_IO_NB;
    actual_token->lexeme = ft_strndup(&line[*i], 1);
    ++(*i);
}