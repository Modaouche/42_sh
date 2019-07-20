/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 08:16:36 by araout            #+#    #+#             */
/*   Updated: 2019/07/20 10:07:55 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

void		print_rev(char **field, int a, int b)
{
	int		i;

	i = get_field_size(field);
	while (--i >= 0)
	{
		ft_printf("%d\t%s\n", a, field[i]);
		if (a > b)
			--a;
		else
			++a;
	}
}

void		print_field(char **field, int a, int b)
{
	int		i;

	i = 0;
	while (field[i])
	{
		if (a > b)
			ft_printf("%d\t", a--);
		else
			ft_printf("%d\t", a++);
		ft_printf("%s\n", field[i++]);
	}
}

int			print_history(int flag, char **field, int a, int b)
{
	if (field == NULL)
		return (0);
	if (get_option(flag, 'r') == 1 || a > b)
		print_rev(field, a, b);
	else
		print_field(field, a, b);
	return (1);
}
