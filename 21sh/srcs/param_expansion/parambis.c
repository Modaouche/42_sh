/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parambis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgheraie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 21:35:30 by mgheraie          #+#    #+#             */
/*   Updated: 2019/07/13 21:35:37 by mgheraie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "param_expansion.h"

char	*param_length(t_param *param)
{
	return (ft_itoa(ft_strlen(param->paramvalue)));
}

char	*remove_small_suf_par(t_param *param)
{
	char	*secondparam;
	char	*paramtmp;
	size_t	i;

	if (!(paramtmp = param->paramvalue))
		return (param->paramvalue);
	paramtmp = param->paramvalue;
	secondparam = param->word;
	i = -1;
	while (paramtmp[++i])
	{
		if (!ft_strcmp(&paramtmp[i], secondparam))
		{
			secondparam = NULL;
			if (!(secondparam = ft_strsub(paramtmp, 0, i)))
				return (NULL);
			return (secondparam);
		}
	}
	return (param->paramvalue);
}

char	*remove_small_pre_par(t_param *param)
{
	char	*paramtmp;
	char	*scdparam;
	size_t	i;
	size_t	j;

	if (!(paramtmp = param->paramvalue))
		return (param->paramvalue);
	scdparam = param->word;
	j = ft_strlen(scdparam);
	i = -1;
	while (paramtmp[++i])
	{
		if (!ft_strncmp(&paramtmp[i], scdparam, j))
		{
			scdparam = NULL;
			if (!(scdparam = ft_strsub(paramtmp, j, ft_strlen(paramtmp) - j)))
				return (NULL);
			return (param->word);
		}
	}
	return (param->paramvalue);
}
