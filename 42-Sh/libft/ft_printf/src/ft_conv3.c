/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 17:03:25 by modaouch          #+#    #+#             */
/*   Updated: 2018/09/04 19:40:15 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_string(va_list ap, t_arg *stk)
{
	stk->conv = (char *)va_arg(ap, char *);
	ft_putstr(stk->conv);
	stk->i += 1;
}

void	ft_char(va_list ap, t_arg *stk)
{
	char	c;

	c = (char)va_arg(ap, int);
	ft_putchar(c);
	stk->i += 1;
}
