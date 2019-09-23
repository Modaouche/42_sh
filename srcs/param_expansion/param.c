/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgheraie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 21:33:20 by mgheraie          #+#    #+#             */
/*   Updated: 2019/09/23 09:29:54 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "param_expansion.h"

char	*param_error(t_param *param)
{
	size_t	sizeparam;

	if (!(param->paramvalue))
		return (ft_joinarg(4, "42sh: ", param->param, ": ", (!*(param->word))
			? PARMSTRERROR : param->word));
	sizeparam = ft_strlen(param->paramvalue);
	if (sizeparam > 0)
		return (param->paramvalue);
	if ((param->signe) & PARAMUNSET)
		return (ft_joinarg(4, "42sh: ", param->line, ": bad substitution"));
	return (NULL);
}

char	*param_use(t_param *param)
{
	size_t sizeparam;

	if (!(param->paramvalue))
		return (param->word);
	sizeparam = ft_strlen(param->paramvalue);
	if (sizeparam > 0)
		return (param->paramvalue);
	if ((param->signe) & PARAMUNSET)
		return (param->word);
	return (NULL);
}

char	*param_alternative(t_param *paramstruct)
{
	char	*param;
	size_t	sizeparam;

	param = paramstruct->paramvalue;
	if ((param) && *param && !((paramstruct->signe) & PARAMUNSET))
		return (paramstruct->word);
	sizeparam = ft_strlen(paramstruct->paramvalue);
	if (sizeparam != 0)
		return (paramstruct->word);
	if ((paramstruct->signe) & PARAMUNSET || !param)
		return (NULL);
	return (paramstruct->word);
}

char	*set_word(t_param *param)
{
	g_shell.envp = set_var_env(param->param, param->word, g_shell.envp);
	return (param->word);
}
