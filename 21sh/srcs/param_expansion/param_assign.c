/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_assign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 09:29:33 by araout            #+#    #+#             */
/*   Updated: 2019/09/23 09:36:40 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "param_expansion.h"

char		*param_assign(t_param *param)
{
	size_t	sizeparam;

	if (!(param->paramvalue))
		return (set_word(param));
	sizeparam = ft_strlen(param->paramvalue);
	if (sizeparam > 0)
		return (param->paramvalue);
	if ((param->signe) & PARAMUNSET)
		return (set_word(param));
	return (NULL);
}

char		pars(char *arg, uint16_t *signe)
{
	size_t i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != ':')
			check_flag(arg, signe, i);
		i++;
	}
	if (*signe != 0 && !check_activeflag(*signe))
	{
		*signe = UIERROR;
		return (0);
	}
	return (1);
}
