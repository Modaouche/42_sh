/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 08:16:36 by araout            #+#    #+#             */
/*   Updated: 2019/07/31 06:13:58 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

void		print_rev(char **field, int a, int b, int flag)
{
	int		i;
	int		tmp;

	i = get_field_size(field);
	while (--i >= 0)
	{
		if (a > b && get_option(flag, 'r'))
		{
			tmp = a;
			a = b;
			b = tmp;
			print_field(field, a, b, flag);
			return ;
		}
		if (a > b && !get_option(flag, 'n'))
			ft_printf("%d\t", a--);
		else if (!get_option(flag, 'n'))
			ft_printf("%d\t", b--);
		else
			ft_printf("\t");
		ft_printf("%s\n", field[i]);
	}
}

void		print_field(char **field, int a, int b, int flag)
{
	int		i;

	i = 0;
	while (field[i])
	{
		if (a > b && !get_option(flag, 'n'))
			ft_printf("%d\t", a--);
		else if (!get_option(flag, 'n'))
			ft_printf("%d\t", a++);
		else
			ft_printf("\t");
		ft_printf("%s\n", field[i++]);
	}
}

int			print_history(int flag, char **field, int a, int b)
{
	if (field == NULL)
		return (0);
	if (get_option(flag, 'r') == 1 || a > b)
		print_rev(field, a, b, flag);
	else
		print_field(field, a, b, flag);
	return (1);
}
