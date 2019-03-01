/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 02:34:36 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/02 09:23:51 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_percent(va_list ap, t_arg *stk)
{
	(void)ap;
	ft_putchar('%');
	stk->i += 1;
}

void	ft_digit(va_list ap, t_arg *stk)
{
	stk->conv = ft_itoa(va_arg(ap, int));
	ft_putstr(stk->conv);
	ft_strdel(&stk->conv);
	stk->i += 1;
}

void	ft_bigdigit(va_list ap, t_arg *stk)
{
	stk->conv = ft_itoa(va_arg(ap, int));
	ft_putstr(stk->conv);
	ft_strdel(&stk->conv);
	stk->i += 1;
}
