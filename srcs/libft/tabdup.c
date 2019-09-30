/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:57:20 by modaouch          #+#    #+#             */
/*   Updated: 2019/07/04 18:19:03 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char **exit_free_prev(char **tab, size_t len)
{
    size_t i;

    i = 0;
    while (i < len)
        ft_strdel(&tab[i++]);
    ft_memdel((void **)&tab);
    return (0);
}

char		**tabdup(char **tab)
{
    char	**new;
    char    *snew;
    size_t  len;
    size_t  i;

    if (!tab || !*tab)
        return (0);
    len = ft_tablen(tab);
    i = 0;
    if (!(new = (char **)ft_memalloc(sizeof(char *) * (len + 1))))
        return (0);
    len = 0;
    while (i < len)
    {
        if (!(snew = strdup(tab[i])))
            return (exit_free_prev(new, i));
        new[i] = snew;
        i++;
    }
    new[len] = NULL;
    return (new);
}
