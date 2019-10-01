/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 11:16:47 by araout            #+#    #+#             */
/*   Updated: 2019/08/28 03:41:57 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

void				set_a_b_under_zero(int *a, int *b)
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

static int			get_range2(char **args, int *a, int *b, int i)
{
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

int					get_range(char **args, int *a, int *b, int i)
{
	if (!valid_operand(args, i))
	{
		if (args[i] && *(args[i]) != '/')
		{
			*a = get_index_fc_by_string(args[i]);
			if (args[i + 1])
				*b = get_index_fc_by_string(args[i + 1]);
			else
				*b = get_hist_nbline() - 1;
			if (*a == -1)
				ft_putstr_fd("21sh: fc: specification out of range\n", 2);
			else
				return (1);
		}
		return (-1);
	}
	*b = 0;
	if (i == -1 && (*b = get_hist_nbline()) > -1)
	{
		*a = *b - 15;
		return (1);
	}
	return (get_range2(args, a, b, i));
}

char				**get_history_field(int a, int b, char **ret, int reverse)
{
	int		size;
	t_list	*head;
	int		i;

	reverse = (a > b);
	(reverse) ? ft_swap_int(&a, &b) : 0;
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

int					get_field_size(char **field)
{
	int		i;

	i = 0;
	while (field && field[i])
		i++;
	return (i);
}
