/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_power_char.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 16:30:30 by modaouch          #+#    #+#             */
/*   Updated: 2018/06/13 16:33:42 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		ft_recursive_power_c(char nb, char power)
{
	char nbr;

	nbr = 1;
	if (power == 0)
		return (1);
	if (power < 0 || nb == 0)
		return (0);
	if (power != 1)
		nbr = ft_recursive_power_c(nb, power - 1);
	if (nb < 0 && power % 2 == 1)
		return (-nbr * -nb);
	return (nbr * nb);
}
