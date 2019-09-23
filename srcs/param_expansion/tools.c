/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgheraie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 21:45:50 by mgheraie          #+#    #+#             */
/*   Updated: 2019/09/23 09:36:16 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "param_expansion.h"

char		*get_word_prm_exp(char *arg, uint16_t signe)
{
	arg += (signe & PARAMDEFAULT) ? 1 : 0;
	arg += (signe & PARAMASSIGN) ? 1 : 0;
	arg += (signe & PARAMERROR) ? 1 : 0;
	arg += (signe & PARAMALTERNATIVE) ? 1 : 0;
	arg += (signe & PARAMUNSET) ? 1 : 0;
	arg += (signe & ONEPER) ? 1 : 0;
	arg += (signe & ONEDIEZ) ? 1 : 0;
	arg += (signe & DOUBLPER) ? 2 : 0;
	arg += (signe & DOUBLDIEZ) ? 2 : 0;
	return (ft_strdup(arg));
}

void		del_struct(t_param **param)
{
	ft_strdel(&((*param)->word));
	ft_strdel(&((*param)->param));
	ft_strdel(&((*param)->paramvalue));
	free(*param);
}

t_param		*init_param(uint16_t signe, char *arg)
{
	t_param *param;
	size_t	i;

	param = NULL;
	if (!(param = (t_param*)malloc(sizeof(t_param))))
		return (NULL);
	param->signe = signe;
	param->line = arg;
	i = -1;
	while (arg[++i] && ft_isalnum(arg[i]))
		;
	param->word = get_word_prm_exp(&arg[i], signe);
	if (!(param->param = ft_strsub(arg, 0, i)))
		return (NULL);
	param->paramvalue = get_env_value(param->param);
	return (param);
}
/*
**		BETWEEN LINE 53 AND 54
**
** param->paramvalue = ft_strdup("VALUE OF PARAM");
** ft_printf("SIGNE = [%d]\n",param->signe);
** ft_printf("ARG = [%s]\n",param->line);
** ft_printf("PARAM = [%s]\n",param->param);
** ft_printf("PARAMVALUE = [%p]\n",param->paramvalue);
** ft_printf("WORD = [%s]\n",param->word);
*/
