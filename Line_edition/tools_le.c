/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_le.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 11:00:19 by modaouch          #+#    #+#             */
/*   Updated: 2019/04/04 16:53:08 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int     is_arrow(char *key)
{
    return ((key[0] == 27 && key[1] == 91 && (key[2] >= 65) && key[2] <= 68)\
    ? key[2] : 0);
}

void    cursor_reposition(size_t n)
{
    while (n)
    {
        tputs(tgetstr("le", NULL), 1, ft_puti);
        n--;
    }
}

void        ft_nlcr(void)
{
    ft_putendl_fd("", STDERR_FILENO);
	tputs(tgetstr("cr", NULL), 1, ft_puti);
}

void		prompt_extend(void)
{
	ft_printf("extend $> ");
}

int             ft_puti(int i)
{
	return (write(STDERR_FILENO, &i, 1));
}
