/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 05:15:09 by araout            #+#    #+#             */
/*   Updated: 2019/07/31 06:15:18 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

int			check_head(t_list *head, char **ret)
{
	if (head == NULL)
	{
		free(ret);
		return (0);
	}
	return (1);
}

int			valid_operand(char **args, int i)
{
	int		flag;

	flag = 1;
	if (i == -1)
		return (1);
	while (args[i])
	{
		if (args[i][0])
		{
			if ((ft_isdigit(args[i][0]) || ((args[i][0] == '-'
							|| args[i][0] == '+') && (ft_isdigit(args[i][1]))))
							&& (flag))
				flag = 1;
			else
				return (0);
		}
		i++;
	}
	return (flag);
}
