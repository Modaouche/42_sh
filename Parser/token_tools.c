/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 22:00:43 by modaouch          #+#    #+#             */
/*   Updated: 2019/03/30 04:44:56 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int     token_isword(int c)
{
    //pour l'instant je le considere comme un alnum mais c'est a changer vite !
    return(ft_isalnum(c));// je ne gere pas les option  d une cmd genre -lra ...^^^^^^
}
int     token_is_io_nb(int c)
{
    (void)c;//^^^^^
    //while ... check si c'est correct... attention avec skip predicate des que tu arrive a la fin 
    return (0);
}

void    skip_predicat(char **line, int *i, int (*pred)(int))
{
    //ft_printf("bef %d, %s, c > %c , c2>%c\n", *i, *line, *(*line + *i), *line[*i]);//*line[*i]);// **line + *i);
    while ((*pred)(line[0][*i]))
    {
        //ft_printf("in>%d, %s, c > %c \n", *i, *line, *(*line + *i));
        (*i)++;
    }
}

int     wordlen(char *line)
{
    int i;
    char *tmp;

    tmp = line;
    i = 0;
    if (!tmp)
        return (0);
    while (tmp[i] && token_isword(tmp[i]))
        i++;
    return (i);
}