/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 15:12:30 by modaouch          #+#    #+#             */
/*   Updated: 2018/04/20 17:58:40 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i] && i < len)
	{
		j = 0;
		while (str[i + j] == to_find[j] && str[i] && to_find[j]
				&& (i + j) < len)
		{
			j++;
			if (!to_find[j])
				return ((char *)&str[i]);
		}
		i++;
	}
	return ((!to_find[0]) ? (char *)str : 0);
}
