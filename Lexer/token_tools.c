/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 22:00:43 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/11 18:34:34 by modaouch         ###   ########.fr       */
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
    while (idx <= 126)
    {
        if (ft_isword(idx))
            g_token_tab[idx] = &token_isword;
        ++idx;
    }
}

void    skip_predicat(const char **line, int *i, int (*pred)(int))
{
    while ((*pred)(line[0][*i]))
        (*i)++;
}