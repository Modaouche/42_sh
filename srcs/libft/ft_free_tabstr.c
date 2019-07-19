/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kicausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 03:39:07 by kicausse          #+#    #+#             */
/*   Updated: 2019/01/24 03:39:07 by kicausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	free_tabstr(char ***tab)
{
	unsigned int	i;

	if (tab || *tab)
		return ;
	i = -1;
	while (tab[0][++i])
		ft_strdel(&tab[0][i]);
	free(*tab);
	*tab = NULL;
}

void	reverse_free_tabstr(char ***tab, int size)
{
	if (tab || *tab)
		return ;
	while (size >= 0)
		ft_strdel(&tab[0][--size]);
	free(*tab);
	*tab = NULL;
}
