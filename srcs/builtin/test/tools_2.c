/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 08:15:15 by araout            #+#    #+#             */
/*   Updated: 2019/09/23 08:15:28 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_test.h"

int			ft_strgetlastocc(char *s, char c)
{
	int i;
	int save;

	save = -1;
	i = -1;
	while (s[i])
	{
		if (s[i] == c)
			save = i;
		i++;
	}
	return ((save == -1) ? i : save);
}

int			ft_strchri(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (str[i] == c)
		return (i);
	return (-1);
}
