/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 22:00:43 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/23 05:18:12 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

t_token_tab g_token_tab[128] =
{
    				[0] = token_iseof,
					[';'] = &token_issemi,
					['\n'] = &token_isnewl,
					['&'] = &token_isamper,
					['|'] = &token_ispipe,
					['!'] = &token_isbang,
					['<'] = &token_isless,
					['>'] = &token_isgreat
};

void    fill_token_tab(void)
{
    size_t idx;

    idx = 33;
    while (idx <= 127)
    {
        if (!ft_strchr(TOKEN_CMP, idx))
            g_token_tab[idx] = &token_isword;
        ++idx;
    }
}

int     for_end_word_inhib(int c)
{
	return (ft_isspace_inhib(c) || (ft_strchr(TOKEN_CMP, c)));
}

int     ft_isspace_inhib(int c)
{
	return (c == ' ' || c == '\t');
}

int     ft_isquote_inhib(int c)
{
	return (c == '\'' || c == '\"');
}


void    skip_predicat(char **line, unsigned int *i, int (*pred)(int))
{
    while ((*pred)(line[0][*i]))
        (*i)++;
}
