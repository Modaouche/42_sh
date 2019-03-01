/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 01:07:15 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/02 01:11:45 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONV_H
# define FT_CONV_H

# include "../includes/ft_printf.h"

t_conv g_convtab[] =
{
	{"%", &ft_percent},
	{"d", &ft_digit},
	{"i", &ft_digit},
	{"D", &ft_bigdigit},
	{"o", &ft_octal},
	{"s", &ft_string},
	{"c", &ft_char},
	{"x", &ft_hex},
	{"X", &ft_hex_up},
	{0, NULL}
};

#endif
