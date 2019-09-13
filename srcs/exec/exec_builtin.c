/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:57:20 by modaouch          #+#    #+#             */
/*   Updated: 2019/07/04 18:19:03 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool		is_builtin(t_ast *ast, char *bu)
{
	unsigned int	i;
	char			**args;

	if (!g_shell.fptr || !g_shell.fptr->flag)
		return (0);
	if (bu == NULL)
	{
		args = get_cmd(ast);
		bu = args[0];
	}
	else
		args = NULL;
	i = 0;
	while (g_shell.fptr->flag[i])
	{
		if (ft_strcmp(bu, g_shell.fptr->flag[i]) == 0)
		{
			ft_free_tab(args);
			return (1);
		}
		++i;
	}
	ft_free_tab(args);
	return (0);
}

bool		exec_builtin(t_ast *ast)
{
	char		ret;
	char		**args;

	args = get_cmd(ast);
	ret = ft_built_in((char*)args);
	ft_free_tab(args);
	g_shell.ret = ret;
	return (ret == 0);
}
