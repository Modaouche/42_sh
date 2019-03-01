/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_occur.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 15:37:46 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/02 00:43:08 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int		ft_occur(const char *str, const char c)
{
	int nb;

	nb = 0;
	if (!(*str) || !str)
		return (0);
	while (*str)
		if (*str++ == c)
			nb++;
	return (nb);
}
