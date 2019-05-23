/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 21:31:42 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/23 09:39:22 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int    backslash(const char *line, char **word, unsigned int *i)
{
    ++(*i);
    if (!line[*i])
    {
        *i = 0;
        return (0);
    }
    else if (line[*i] == '\n')
        ++(*i);
    else if (ft_strchr(DQUOTE_CMP,line[*i]))
    {
        *word = ft_strjoin_free(*word, (char *)line + *i, 1);
        ++(*i);
    }
    else
        --(*i);
    return (1);
}

void    backslash_end(t_edit *line_e)
{
    init_line(line_e);
	line_e->prompt_size = print_prompt(7);
    line_edition(line_e);
    if (!line_e->line)
        line_e->line = ft_memalloc(1);
}

void    dollars_cmd(const char *line, char **word, unsigned int *i)
{
    ++(*i);    
    if (line[*i] == '$')
        ft_putstr("~[  $$  ]~\n");//pidofshell(word);//to creat
    else if (line[*i] == '(')
        ft_putstr("~[  $(  ]~\n");//substition(word, line[*i], i);//to creat
    else if (line[*i] == '{')
        ft_putstr("~[  ${  ]~\n");//word_expansion(word, line[*i], i);//to creat
    else if (line[*i] == '\\' || line[*i] == ' '\
        || line[*i] == '\t' || !line[*i])
        *word = (!*word) ? ft_strdup("$") : ft_strjoin_free(*word, "$", 1);
    else if (ft_isalnum(line[*i]))
        ft_putstr("~[  $VAR  ]~\n");//get_varenv();//to creat
}