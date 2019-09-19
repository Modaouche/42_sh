/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgheraie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 01:34:10 by mgheraie          #+#    #+#             */
/*   Updated: 2019/09/18 03:08:21 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "param_expansion.h"
#include <stdio.h>

char	*dispatch(t_param *param)
{
	char		*(*tabfct[10])(t_param *param);
	uint16_t	oct;
	size_t		i;

	oct = 1;
	i = -1;
	tabfct[0] = &no_param;
	tabfct[1] = &param_use;
	tabfct[2] = &param_assign;
	tabfct[3] = &param_error;
	tabfct[4] = &param_alternative;
	tabfct[5] = &param_length;
	tabfct[6] = &remove_small_suf_par;
	tabfct[7] = &remove_small_pre_par;
	tabfct[8] = &remove_small_suf_par;
	tabfct[9] = &remove_small_pre_par;
	char *res = NULL;
	while (oct != UIERROR)
	{
		if (oct & PARAMUNSET)
			oct = oct << 1;
		if (oct & (param->signe) && ++i)
			res = ft_strdup((tabfct[i](param)));
		oct = oct << 1;
	}
	if (!res)
	    res = ft_strdup(no_param(param));
	return (res);
}

char	*param_expansion(char *arg)
{
	uint16_t	signe;
	t_param		*param;
	char		*res;

	signe = 0;
	if (!(pars(arg, &signe)))
		return (NULL);
	if (!(param = init_param(signe, arg)))
		return (NULL);
	res = dispatch(param);
	del_struct(&param);
	return (res);
}

int main(int ac, char **av, char **envp)
{
	g_env = envp;
	char *s = param_expansion(av[1]);
	(void)ac;
	printf("%s\n", s);
	return (0);
}
