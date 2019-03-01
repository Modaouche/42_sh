/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prec1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 15:28:28 by modaouch          #+#    #+#             */
/*   Updated: 2018/06/23 20:15:41 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_space(va_list ap, t_arg *stk)
{
	int i;

	i = 0;
	stk->space = va_arg(ap, int);
	while (i++ < stk->space)
		ft_putchar(' ');
	stk->i += 1;
}
