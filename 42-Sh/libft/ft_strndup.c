/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 18:14:04 by modaouch          #+#    #+#             */
/*   Updated: 2018/05/29 18:06:48 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(const char *str, size_t n)
{
	char	*dest;
	size_t	i;
	size_t	j;

	j = 0;
	i = ft_strlen(str);
	if (!(dest = (char *)malloc(sizeof(*dest) * (i + 1))))
		return (0);
	while (j < i && n--)
	{
		dest[j] = str[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}
