/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 14:54:34 by modaouch          #+#    #+#             */
/*   Updated: 2018/04/20 23:32:43 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *s, int c, size_t n)
{
	char	*str;
	size_t	i;
	char	cha;

	i = 0;
	cha = (char)c;
	str = (char *)s;
	while (i < n)
	{
		if (str[i] == cha)
			return (str + i);
		i++;
	}
	return (0);
}
