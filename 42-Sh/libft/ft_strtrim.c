/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 15:04:58 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/15 18:49:24 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_parsing(char const *s)
{
	int			j;
	int			i;
	int			len;

	j = 0;
	len = ft_strlen(s);
	i = len - 1;
	while (ft_isspace(s[j]))
		j++;
	if (!s[j])
		return (0);
	while (ft_isspace(s[i]))
	{
		i--;
		j++;
	}
	return (len - j);
}

static char		*ft_remplissage(const char *s, char *str, int j)
{
	int			i;
	int			k;

	i = 0;
	while (s[j])
	{
		if (ft_isspace(s[j]))
		{
			k = 0;
			while (ft_isspace(s[j + k]))
				k++;
			if (!s[j + k])
				break ;
		}
		str[i] = s[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char			*ft_strtrim(char const *s)
{
	char		*str;
	int			i;
	int			j;

	if (!s)
		return (0);
	i = ft_parsing(s);
	if (!(str = ft_strnew(i)))
		return (0);
	j = 0;
	while (ft_isspace(s[j]))
		j++;
	str = ft_remplissage(s, str, j);
	return (str);
}
