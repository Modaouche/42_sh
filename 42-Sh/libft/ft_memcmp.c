/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 14:54:49 by modaouch          #+#    #+#             */
/*   Updated: 2018/04/20 17:03:35 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*tmps1;
	unsigned char	*tmps2;

	tmps1 = (unsigned char *)s1;
	tmps2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	n--;
	while (*tmps1 == *tmps2 && n--)
	{
		tmps1++;
		tmps2++;
	}
	return ((unsigned char)*tmps1 - (unsigned char)*tmps2);
}
