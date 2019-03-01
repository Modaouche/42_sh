/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 19:31:09 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/02 09:25:20 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_octal(va_list ap, t_arg *stk)
{
	(void)ap;
	stk->conv = ft_itoa_base((int)va_arg(ap, int), 8);
	ft_putstr(stk->conv);
	ft_strdel(&stk->conv);
	stk->i += 1;
}

void	ft_hex(va_list ap, t_arg *stk)
{
	int	i;

	(void)ap;
	i = 0;
	stk->conv = ft_itoa_base((int)va_arg(ap, int), 16);
	while (stk->conv[i])
	{
		stk->conv[i] = ft_tolower(stk->conv[i]);
		i++;
	}
	ft_putstr(stk->conv);
	ft_strdel(&stk->conv);
	stk->i += 1;
}

void	ft_hex_up(va_list ap, t_arg *stk)
{
	int	i;

	(void)ap;
	i = 0;
	stk->conv = ft_itoa_base((int)va_arg(ap, int), 16);
	while (stk->conv[i])
	{
		stk->conv[i] = ft_toupper(stk->conv[i]);
		i++;
	}
	ft_putstr(stk->conv);
	ft_strdel(&stk->conv);
	stk->i += 1;
}
