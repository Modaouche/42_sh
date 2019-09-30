/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_flag_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgheraie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 05:37:51 by mgheraie          #+#    #+#             */
/*   Updated: 2019/06/16 05:50:11 by mgheraie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_test.h"

char			test_nbr_error(char **arg)
{
	if (arg[0] && test_get_id_flag(arg[0]) != FALSE)
		ft_printf("ft_test: unknown condition: %s\n", arg[0]);
	else if (arg[0] && test_get_id_flag(arg[0]) == FALSE)
		ft_printf("42sh: parse error: condition expected: %s\n", arg[0]);
	return (1);
}

void			print_no_int(char **args)
{
	int i;

	i = -1;
	while (args[0][++i])
	{
		if ((args[0][i] < '0' || args[0][i] > '9') && (args[0][i] != '-'
					|| args[0][i] != '+'))
		{
			ft_printf("%s\n", args[0]);
			return ;
		}
	}
	while (args[2][++i])
	{
		if ((args[2][i] < '0' || args[2][i] > '9') && (args[2][i] != '-'
					|| args[2][i] != '+'))
		{
			ft_printf("%s\n", args[2]);
			return ;
		}
	}
}

char			test_pars_nbr(char **args)
{
	if (ft_dstrlen(args) == 2)
		return (test_nbr_error(args));
	if (ft_dstrlen(args) > 3)
		return (ft_printf("ft_test : too many arguments\n") ? FALSE : FALSE);
	if ((!args[0] || !args[2]) || ft_strchr(args[0], '.')
			|| ft_strchr(args[0], ',') || ft_strchr(args[2], '.')
			|| ft_strchr(args[2], ','))
	{
		ft_printf("test: integer expression expected: ");
		print_no_int(args);
		return (ERROR);
	}
	return (TRUE);
}

char			test_flag_nbr(uint16_t flag, void *s)
{
	char	**args;
	int		nb1;
	int		nb2;
	int		res;

	res = FALSE;
	args = (char**)s;
	if (test_pars_nbr(args) == FALSE)
		return (FALSE);
	nb1 = ft_atoi(args[0]);
	nb2 = ft_atoi(args[2]);
	(flag == TEST_EQ && nb1 == nb2) ? res = TRUE : 0;
	(flag == TEST_NE && nb1 != nb2) ? res = TRUE : 0;
	(flag == TEST_GE && nb1 >= nb2) ? res = TRUE : 0;
	(flag == TEST_LT && nb1 < nb2) ? res = TRUE : 0;
	(flag == TEST_LE && nb1 <= nb2) ? res = TRUE : 0;
	return (res);
}
