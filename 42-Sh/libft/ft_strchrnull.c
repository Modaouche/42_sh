/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrnull.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:11:43 by modaouch          #+#    #+#             */
/*   Updated: 2018/04/21 00:17:04 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchrnull(const char *s, int c)
{
	char	cha;
	char	*str;

	cha = (char)c;
	str = (char *)s;
	if (!s)
		return (0);
	while (*str != cha && *str)
		str++;
	return (str);
}
