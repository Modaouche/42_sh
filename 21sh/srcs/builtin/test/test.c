/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgheraie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 00:43:44 by mgheraie          #+#    #+#             */
/*   Updated: 2019/09/23 08:14:12 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_test.h"

char			ft_test(uint16_t flag, char **arg)
{
	char		(*tabfct[3])(uint16_t flag, void *arg);

	tabfct[0] = test_flag_file;
	tabfct[1] = test_flag_str;
	tabfct[2] = test_flag_nbr;
	if (arg[1] && flag <= TEST_S)
		return (tabfct[0](flag, arg[1]));
	else if (arg[1] && flag == TEST_Z)
		return ((arg[1] && !ft_strlen(arg[1])) ? FALSE : TRUE);
	else if (arg && flag <= TEST_DIFF)
		return (tabfct[1](flag, arg));
	return (tabfct[2](flag, arg));
}

int				ft_test_main(char **av)
{
	uint16_t	flag;
	char		test;
	uint8_t		bool_test;

	if (!av || !av[0] || !av[1])
		return (1);
	av += 1;
	test = FALSE;
	bool_test = FALSE;
	if (!ft_strcmp(*av, "!"))
	{
		bool_test = TRUE;
		av++;
	}
	flag = ERROR;
	if (av[0] != NULL && av[1] == NULL)
		return (FALSE);
	if ((flag = test_set_id_flag(av)) == FALSE)
		return (TRUE);
	test = ft_test(flag, av);
	if (bool_test == TRUE)
		test = !test;
	return (test);
}
