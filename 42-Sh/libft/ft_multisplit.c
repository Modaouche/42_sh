/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multisplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 15:04:08 by modaouch          #+#    #+#             */
/*   Updated: 2019/01/21 02:59:46 by modaouch         ###   ########.fr       */
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

static int		ft_strlen_cs(char const *s, char *clv, int button)
{
	int			i;
	int			n;

	i = 0;
	n = 0;
	if (button == 1)
	{
		while (s[i])
		{
			if (!ft_match_char(s[i], clv))
			{
				n++;
				while (!ft_match_char(s[i], clv) && s[i])
					i++;
			}
			if (s[i])
				i++;
		}
		return (n);
	}
	while (s[i] && !ft_match_char(s[i++], clv) && s)
		n++;
	return (n);
}

static char		**ft_prefilling(char **tab, char const *s, char *clv)
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
		if (!ft_match_char(s[i], clv))
		{
			len = ft_strlen_cs(&s[i], clv, 2);
			if (!(tabstr[n] = ft_strnew(len)))
				return (ft_nfree(tabstr, --n));
			tabstr[n] = ft_strncpy(tabstr[n], &s[i], len);
			while (s[i + 1] && !ft_match_char(s[i], clv))
				i++;
			n++;
		}
		i++;
	}
	return (tab);
}

char			**ft_multisplit(char const *s, char *cleaver)
{
	int			lentab;
	char		**tab;

	if (!s || !*s || !cleaver)
		return (0);
	lentab = ft_strlen_cs(s, cleaver, 1);
	if (!(tab = (char **)malloc(sizeof(*tab) * (lentab + 1))))
		return (0);
	tab[lentab] = NULL;
	if (!(ft_prefilling(tab, s, cleaver)))
	{
		free(tab);
		return (NULL);
	}
	return (tab);
}
