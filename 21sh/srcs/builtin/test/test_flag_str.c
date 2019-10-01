/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_flag_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgheraie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 05:36:42 by mgheraie          #+#    #+#             */
/*   Updated: 2019/06/16 05:50:13 by mgheraie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_test.h"

void			test_get_strflag(uint16_t flag)
{
	(flag == TEST_EQUAL) ? ft_printf(TEST_STREQUAL"\n") : 0;
	(flag == TEST_DIFF) ? ft_printf(TEST_STRDIFF"\n") : 0;
}

char			test_flag_str(uint16_t flag, void *s)
{
	char	**args;
	char	*arg1;
	char	*arg2;

	args = (char**)s;
	if (!args[1] || !args[2])
	{
		ft_printf("21sh: parse error: condition expected: ");
		test_get_strflag(flag);
		return (ERROR);
	}
	arg1 = args[0];
	arg2 = args[2];
	if (flag == TEST_EQUAL)
	{
		if (ft_strcmp(arg1, arg2) == 0)
			return (TRUE);
		return (FALSE);
	}
	if (flag == TEST_DIFF)
		return ((ft_strcmp(arg1, arg2) != 0) ? TRUE : FALSE);
	return (ERROR);
}

char			test_flag_z(uint16_t flag, void *s)
{
	(void)flag;
	return ((ft_strlen(s) == 0) ? TRUE : FALSE);
}
