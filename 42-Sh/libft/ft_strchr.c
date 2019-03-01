/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:11:21 by modaouch          #+#    #+#             */
/*   Updated: 2018/04/21 00:26:51 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	char	cha;
	char	*str;

	cha = (char)c;
	str = (char *)s;
	while (*str != cha && *str)
		str++;
	if (*str == cha)
		return (str);
	return (0);
}
