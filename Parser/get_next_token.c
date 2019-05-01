/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 08:50:32 by modaouch          #+#    #+#             */
/*   Updated: 2019/04/18 14:33:36 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

t_token    *get_next_token(char **line, int *i)
{
    t_token     *actual_token;
    char         c;

    if (!(actual_token = (t_token*)ft_memalloc(sizeof(t_token))))
        return (0);
    if (*line && line[0][*i] != '\n')//pb car si on a un space apres un '\n'// yes confirmed FT_ISSPACE tochange
        skip_predicat(line, i, &ft_isspace);
    actual_token->lexeme = NULL;
    if (!*line || line[0][*i] == '\0')
    {
        actual_token->tokind = T_EOF;
        return (actual_token);
    }
    c = line[0][*i];
    ++(*i);
    if (c == ';')
    {
        actual_token->tokind = T_SEMI;
        actual_token->lexeme = ft_strdup(";");
        return (actual_token);
    }
    else if (c == '\n')
    {
        actual_token->tokind = T_NEWL;
        actual_token->lexeme = ft_strdup("\n");//maybe after to check newl check if the next one is eof('\0')
        return (actual_token);
    }
    else if (c == '&')
    {
        actual_token->tokind = T_AMPER;
        actual_token->lexeme = ft_strdup("&");
        if (line[0][*i] == '&'/* && line[0][*i + 1]*/)//mis en commentaire mais je crois que je le gere dans le parser ;) to check
        {
            ++(*i);
            actual_token->tokind = T_AND_IF;
            actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, "&", 1);
        }
        return (actual_token);
    }
    else if (c == '|')
    {
        actual_token->tokind = T_PIPE;
        actual_token->lexeme = ft_strdup("|");
        if (line[0][*i] == '|'/* && line[0][*i + 1]*/)
        {
            ++(*i);
            actual_token->tokind = T_OR_IF;
            actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, "|", 1);
        }
        return (actual_token);
    }
    else if (c == '!')
    {
        actual_token->tokind = T_BANG;
        actual_token->lexeme = ft_strdup("!");
        return (actual_token);
    }
    else if (c == '>')
    {
        actual_token->tokind = T_GREAT;
        actual_token->lexeme = ft_strdup(">");
        if (line[0][*i] == '>')
        {
            ++(*i);
            actual_token->tokind = T_DGREAT;
            actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, ">", 1);
        }
        else if (line[0][*i] == '&')
        {
            ++(*i);
            actual_token->tokind = T_GREATAND;
            actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, "&", 1);
        }
        else if (line[0][*i] == '|')
        {
            ++(*i);
            actual_token->tokind = T_CLOBBER;
            actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, "|", 1);
        }
        return (actual_token);
    }
    else if (c == '<')
    {
        actual_token->tokind = T_LESS;
        actual_token->lexeme = ft_strdup("<");
        if (line[0][*i] == '<')
        {
            ++(*i);
            actual_token->tokind = T_DLESS;
            actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, "<", 1);
            if (line[0][*i] == '-')
            {
                ++(*i);
                actual_token->tokind = T_DLESSDASH;
                actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, "-", 1);
            }
        }
        else if (line[0][*i] == '&')
        {
            ++(*i);
            actual_token->tokind = T_LESSAND;
            actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, "&", 1);
        }
        else if (line[0][*i] == '>')
        {
            ++(*i);
            actual_token->tokind = T_LESSGREAT;
            actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, ">", 1);
        }
        return (actual_token);
    }
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
    actual_token->tokind = T_ERROR;
    return (actual_token);
}
