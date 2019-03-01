/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:14:04 by modaouch          #+#    #+#             */
/*   Updated: 2018/10/22 22:39:46 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *str)
{
	char	*dest;
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(str);
	dest = (char *)malloc(sizeof(*dest) * (i + 1));
	if (dest == NULL)
		return (0);
	while (j < i)
	{
		dest[j] = str[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}
