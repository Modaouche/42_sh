/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 15:51:13 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/23 09:39:42 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int    word_handling_prime(const char *line, char **word, unsigned int *i, int qt)
{
    if (line[*i] == '\"' || (!qt && (!line[*i] || (for_end_word_inhib(line[*i])\
        || line[*i] == '\''))))
    {
        if (qt)
            ++(*i);
        return (0);
    }
    else if (!line[*i])
    {
        *i = 0;
        *word = (!*word) ? ft_strdup("\n") : ft_strjoin_free(*word, "\n", 1);
        return (0);
    }
    else if (line[*i] == '\\')
    {
        if (!backslash(line, word, i, qt))
            return (0);
    }
    else if (line[*i] == '~')
        insert_home_path(line, word, i);
    else if (line[*i] == '$')
        dollars_cmd(line, word, i);
    else
        *word = (!*word) ? ft_strndup(line + *i, 1) :\
                ft_strjoin_free(*word, ft_strndup(line + *i, 1), 3);
    return (1);
}

char    *word_handling(const char *line, unsigned int *i, int qt)
{
    char *word;

    word = NULL;
    while (word_handling_prime(line, &word, i, qt))
        ++(*i);
    return (word);
}

int     word_parser(const char *line, char **word, int qt)
{
    unsigned int i;
    char *buff;

    i = 0;
    if (qt == 1)
        ++i;
    if (!*word)
    {
        *word = word_handling(line , &i, qt);
        return (i);
    }
    else
    {
        if ((buff = word_handling(line, &i, qt)))
            *word = ft_strjoin_free(*word, buff, 3);
    }
    return (i);
}
