/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 17:38:23 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 01:39:19 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void    token_isword(t_token *actual_token, const char *line, unsigned int *i)
{
    char *word;

    word = get_word(&(line[*i]));
    if (ft_isdigit(line[*i]) && (line[*i + 1] == '<' || line[*i + 1] == '>'))// peut etre to change into word ou bien ajouter une condition pour getword
        token_isio_nb(actual_token, line, i);
    else
    {      
        actual_token->tokind = T_WORD;
        actual_token->lexeme = word;
        skip_predicat(&line, i, &ft_isword);
    }
}

void    token_isio_nb(t_token *actual_token, const char *line, unsigned int *i)
{
    (void)line;
    (void)actual_token;
    (*i)++;
}

/*
    else if (token_is_io_nb(c))
    {
        // skip_predicat(line, i, &token_is_io_nb);
        // actual_token->tokind = T_IO_NB;
        // actual_token->lexeme = ft_strndup(&(line[0][*i - 1]), wordlen(&(line[0][*i - 1])));
        // return (actual_token);
    }
    else if (token_isword(c))
    {
        actual_token->tokind = T_WORD;
        actual_token->lexeme = ft_strndup(&(line[0][*i - 1]), wordlen(&(line[0][*i - 1])));
        skip_predicat(line, i, &token_isword);
        return (actual_token);
    }


    
int     token_isio_nb(char c)
{
    (void)c;//^^^^^
    //while ... check si c'est correct... attention avec skip predicate des que tu arrive a la fin 
    return (0);
}
*/