/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inhibitors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 15:48:28 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/11 18:35:16 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
/*
int     *ext_quotes(const char *line, char *word)
{
    static int var_ext[3] = {0};

    if (*line == 39)
    {
        var_ext[0] = !var_ext[0] ? 1 : 0;
        
    }
    else if (!var_ext[0] && *line == 34)
        var_ext[1] = 1;
    return (var_ext);
}
*//*
        special :  |  &  ;  <  >  (  )  $  `  \  "  '  *   ?   [   #   ˜   =   %  !
*/

int     ft_isword(int c)
{
    if ((ft_isalnum(c) || (c > 42 && c < 48)) || (c >= 93 && c <= 95))
        return (1);
    return (0);
}

char    *get_word(const char *line)
{
    size_t  i;
    int     *var_ext;
    char    *word;

    i = 0;
    word = NULL;
    var_ext = NULL;
    (void)var_ext;
    while (line[i] && ft_isword(line[i]))
        i++;
    //if (i == 0 && (line[i] == 39 || (line[i] == 34 || line[i] == 96)))
    //    var_ext = ext_quotes(line, word);
    //else
        word = ft_strndup(line, i);
    /*while (var_ext && var_ext[0] && var_ext[1] && var_ext[2])
    {
        var_ext = ext_quotes(line, word);
    }*/
    return (word);
}