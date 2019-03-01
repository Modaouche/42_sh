/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 18:44:04 by modaouch          #+#    #+#             */
/*   Updated: 2018/05/29 18:09:13 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcdup(const char *str, char c)
{
	char	*dest;
	size_t	i;
	size_t	j;

	j = 0;
	i = ft_strlen(str);
	if (!(dest = (char *)malloc(sizeof(*dest) * (i + 1))))
		return (0);
	while (j < i && str[j] != c)
	{
		dest[j] = str[j];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}
