/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 11:16:46 by modaouch          #+#    #+#             */
/*   Updated: 2019/03/16 19:02:38 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

# define HOME_VAR ""

void	builtin_exit(char **args)
{
	unsigned char	returnValue;

	if (args[0] == NULL)
		exit(0);
	else if (args[1] != NULL)
		ft_putendl("exit: too many arguments");
	else
	{
		if (!ft_strisdigit(args[0]))
		{
			ft_printf("exit: %s: numeric argument required", args[0]);
			exit(-1);
		}
		returnValue = ft_atoi(args[0]);
		exit(returnValue);
	}
}
