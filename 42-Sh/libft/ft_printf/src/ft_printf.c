/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 15:09:45 by modaouch          #+#    #+#             */
/*   Updated: 2018/12/13 12:09:25 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_conv.h"
#include "../includes/ft_printf.h"
#include <string.h>

static int		ft_n_precision(const char *format)
{
	if (format[0] == 'n')
		return (1000);
	return (-1);
}

static int		ft_n_conv(const char *format)
{
	int			n;

	n = 0;
	while (g_convtab[n].conv)
	{
		if (!ft_strncmp(g_convtab[n].conv, format,\
			ft_strlen(g_convtab[n].conv)))
			return (n);
		n++;
	}
	return (-1);
}

static void		ft_init(t_arg *stk)
{
	stk->i = 0;
	stk->n = 0;
	stk->space = 0;
}

int				ft_printf(const char *format, ...)
{
	va_list		argptr;
	t_arg		stk;

	ft_init(&stk);
	va_start(argptr, format);
	while (format[stk.i])
	{
		if (format[stk.i] == '%')
		{
			stk.n = ft_n_precision(&format[++stk.i]);
			(stk.n > -1) ? ft_space(argptr, &stk) : 0;
			stk.n = ft_n_conv(&format[stk.i]);
			(stk.n > -1) ? g_convtab[stk.n].convert(argptr, &stk) : 0;
		}
		else
			ft_putchar(format[stk.i++]);
	}
	va_end(argptr);
	return (0);
}
