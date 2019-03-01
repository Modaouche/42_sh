/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 16:58:15 by modaouch          #+#    #+#             */
/*   Updated: 2018/04/20 16:58:45 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_strnbr(long nb, char *strnbr, int i)
{
	long		nb2;

	nb2 = nb;
	if (i == -1)
	{
		strnbr[i + 1] = '-';
		i += 2;
	}
	if (nb2 > 9)
	{
		i = ft_strnbr(nb2 / 10, strnbr, i);
		i = ft_strnbr(nb2 % 10, strnbr, i);
	}
	else
	{
		strnbr[i] = nb2 + '0';
		return (i + 1);
	}
	return (i);
}

static void		ft_to_sign(long *n, int *len, int *signe)
{
	*signe = -1;
	*len = 2;
	*n = *n * (-1);
}

char			*ft_itoa(int nb)
{
	char		*strnbr;
	int			signe;
	int			len;
	long		i;
	long		n;

	n = nb;
	i = 9;
	len = 1;
	signe = 0;
	if (n < 0)
		ft_to_sign(&n, &len, &signe);
	while (i < n)
	{
		i *= 10;
		len++;
	}
	if (!(strnbr = ft_strnew(len)))
		return (0);
	i = ft_strnbr(n, strnbr, signe);
	strnbr[i] = '\0';
	return (strnbr);
}
