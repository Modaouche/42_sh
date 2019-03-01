/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 15:03:53 by modaouch          #+#    #+#             */
/*   Updated: 2018/04/20 17:57:34 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	int		i;

	if (!ft_strchr(s, c))
		return (NULL);
	i = ft_strlen(s);
	while (s[i] != c)
		i--;
	return ((char *)s + i);
}
