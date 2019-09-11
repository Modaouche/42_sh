/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgheraie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 00:43:44 by mgheraie          #+#    #+#             */
/*   Updated: 2019/06/16 05:50:34 by mgheraie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_test.h"

char			ft_test(uint16_t flag, char **arg)
{
	char		(*tabfct[3])(uint16_t flag, void *arg);
	char		res;

	res = FALSE;
	tabfct[0] = test_flag_file;
	tabfct[1] = test_flag_str;
	tabfct[2] = test_flag_nbr;
	if (arg[1] && flag <= TEST_S)
		return (tabfct[0](flag, arg[1]));
	else if (arg[1] && flag == TEST_Z)
		return ((arg[1] && !ft_strlen(arg[1])) ? TRUE : FALSE);
	else if (arg && flag <= TEST_DIFF)
		return (tabfct[1](flag, arg));
	return (tabfct[2](flag, arg));
}

int			ft_test_main(void *arg)
{
	uint16_t	flag;
	char		test;
	uint8_t		bool_test;
	char		**av;

	av = (char**)arg;
	test = TRUE;
	bool_test = FALSE;
	if (!ft_strcmp(*av, "!"))
	{
		bool_test = TRUE;
		av++;
	}
	flag = ERROR;
	if (av[0] != NULL && av[1] == NULL)
	{
	ft_printf("RESULT = TRUE\n");
		return (TRUE);
	}
	if ((flag = test_set_id_flag(av)) == FALSE)
	{
	ft_printf("RESULT = FALSE\n");
		return (FALSE);
	}
	test = ft_test(flag, av);
	if (bool_test == TRUE)
		test = !test;
	ft_printf("RESULT = %d\n", test);
	return (test);
}
