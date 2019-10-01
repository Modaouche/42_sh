/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgheraie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 02:17:36 by mgheraie          #+#    #+#             */
/*   Updated: 2019/09/23 10:56:49 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int			get_first_word(char **str, int *check)
{
	int i;
	int j;

	i = 0;
	while (str[i] && str[i][0] == '-')
	{
		j = 1;
		while (str[i][j])
		{
			if (str[i][j] != 'n')
				return (i + 1);
			j++;
		}
		i++;
		*check = 1;
	}
	return (i + 1);
}

int			ft_echo(char **args)
{
	int		i;
	int		check;

	if (!args || !*args)
		return (1);
	check = 0;
	i = get_first_word(args + 1, &check);
	while (args[i])
	{
		ft_putstr(args[i]);
		(args[i + 1]) ? write(1, " ", 1) : 0;
		i++;
	}
	if (check != 1)
		ft_putendl("");
	return (0);
}
