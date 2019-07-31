/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 11:16:47 by araout            #+#    #+#             */
/*   Updated: 2019/07/31 06:15:49 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

static void		set_a_b_under_zero(int *a, int *b)
{
	if (*a == 0 || *b == 0)
	{
		if (*a == 0)
			*a = get_hist_nbline() + *a;
		if (*b == 0)
			*b = get_hist_nbline() + *b;
	}
	if (*a < 0 || *b < 0)
	{
		if (*a < 0)
			*a = get_hist_nbline() + *a + 1;
		if (*b < 0)
			*b = get_hist_nbline() + *b + 1;
	}
	if (*a > get_hist_nbline() || *b > get_hist_nbline())
	{
		if (*a > 0)
			*a = get_hist_nbline();
		if (*b > 0)
			*b = get_hist_nbline();
	}
	if (*a < 0)
		*a = get_hist_nbline();
	if (*b < 0)
		*b = get_hist_nbline();
}

int				get_range(char **args, int *a, int *b, int i)
{
	if (!valid_operand(args, i))
	{
		ft_putstr_fd("bash: fc: history specification out of range\n", 2);
		return (-1);
	}
	*b = 0;
	if (i == -1 && (*b = get_hist_nbline()) > -1)
	{
		*a = *b - 15;
		return (1);
	}
	if (args[i])
		*a = ft_atoi(args[i]);
	if (args[i] && args[++i])
		*b = ft_atoi(args[i]);
	else if (*a <= 0)
	{
		if (*a == 0)
			*a = -1;
		*b = get_hist_nbline();
		*a = *b + *a + 1;
	}
	set_a_b_under_zero(a, b);
	return (1);
}

char			**get_history_field(int a, int b, char **ret, int reverse)
{
	int		size;
	t_list	*head;
	int		i;

	reverse = (a > b);
	if (reverse)
		ft_swap_int(&a, &b);
	size = b - a;
	if (!(ret = (char **)ft_memalloc(sizeof(char *) * (size + 2))))
		return (NULL);
	head = g_shell.history->hist;
	i = 0;
	while (++i < a && head)
		head = head->next;
	if (!(check_head(head, ret)))
		return (NULL);
	while (i <= b && head)
	{
		ret[i - a] = ((t_hnode *)head->content)->cmd;
		head = head->next;
		++i;
	}
	if (!(check_head(head, ret)))
		return (NULL);
	return (ret);
}

int				get_field_size(char **field)
{
	int		i;

	i = 0;
	while (field && field[i])
		i++;
	return (i);
}
