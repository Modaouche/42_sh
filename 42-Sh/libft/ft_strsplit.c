/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 15:04:08 by modaouch          #+#    #+#             */
/*   Updated: 2019/01/21 02:58:21 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**ft_nfree(char **tab, int n)
{
	if (n == 0)
		return (0);
	while (n > 0)
		free(tab[n--]);
	free(tab[0]);
	return (0);
}

static int		ft_strlen_cs(char const *s, char c, int button)
{
	int			i;
	int			n;

	i = 0;
	n = 0;
	if (button == 1)
	{
		while (s[i])
		{
			if (s[i] != c)
			{
				n++;
				while (s[i] != c && s[i])
					i++;
			}
			if (s[i])
				i++;
		}
		return (n);
	}
	while (s[i] && s[i++] != c && s)
		n++;
	return (n);
}

static char		**ft_preremplissage(char **tab, char const *s, char c)
{
	int			i;
	int			len;
	char		**tabstr;
	int			n;

	tabstr = tab;
	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			len = ft_strlen_cs(&s[i], c, 2);
			if (!(tabstr[n] = ft_strnew(len)))
				return (ft_nfree(tabstr, --n));
			tabstr[n] = ft_strncpy(tabstr[n], &s[i], len);
			while (s[i + 1] && s[i] != c)
				i++;
			n++;
		}
		i++;
	}
	return (tab);
}

char			**ft_strsplit(char const *s, char c)
{
	int			lentab;
	char		**tab;

	if (!s)
		return (0);
	lentab = ft_strlen_cs(s, c, 1);
	if (!(tab = (char **)malloc(sizeof(*tab) * (lentab + 1))))
		return (0);
	if (!(ft_preremplissage(tab, s, c)))
	{
		free(tab);
		return (NULL);
	}
	tab[lentab] = NULL;
	return (tab);
}
