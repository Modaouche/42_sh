/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 15:09:38 by modaouch          #+#    #+#             */
/*   Updated: 2018/11/02 09:22:48 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "../src/libft/libft.h"

typedef struct	s_arg
{
	char		type;
	char		*conv;
	int			space;
	int			i;
	int			n;
}				t_arg;

typedef struct	s_conv
{
	char		*conv;
	void		(*convert)(va_list ap, t_arg *stk);
}				t_conv;

int				ft_printf(const char *format, ...);
int				ft_analyse(t_arg *stk);
void			ft_space(va_list ap, t_arg *stk);
void			ft_percent(va_list ap, t_arg *stk);
void			ft_digit(va_list ap, t_arg *stk);
void			ft_bigdigit(va_list ap, t_arg *stk);
void			ft_char(va_list ap, t_arg *stk);
void			ft_hex(va_list ap, t_arg *stk);
void			ft_hex_up(va_list ap, t_arg *stk);
void			ft_octal(va_list ap, t_arg *stk);
void			ft_string(va_list ap, t_arg *stk);
#endif
