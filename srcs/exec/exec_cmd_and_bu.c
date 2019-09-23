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

void		free_completed_jobs(void)
{
	update_status();
	if (g_shell.errorno)
		error_msg("./42sh");
	remove_completed_job(&g_shell.first_job);
}

bool		is_builtin(char *bu)
{
	unsigned int	i;

	if (!g_shell.fptr || !g_shell.fptr->flag)
		return (0);
	i = 0;
	while (g_shell.fptr->flag[i])
	{
		if (ft_strcmp(bu, g_shell.fptr->flag[i]) == 0)
			return (1);
		++i;
	}
	return (0);
}

bool		exec_builtin(char **args)
{
	char		ret;

	ret = ft_built_in((char*)args);
	ft_free_tab(args);
	g_shell.ret = (ret == 0);
	return (ret == 0);
}

bool		exec_cmd(t_ast *ast, bool is_redir_pipe) 
{
	char **args;

	args = get_cmd(ast);
	ft_putendl("-----------------[ exec cmd ]");
	if (!is_redir_pipe && is_builtin(args[0]))
		return (exec_builtin(args));
	ft_free_tab(args);
	push_back_job(ast);
	g_shell.errorno = NO_ERROR;
	launch_job(last_job());
	if (g_shell.errorno)
	{
		remove_completed_job(&g_shell.first_job);
		error_msg("./42sh");
	}
	return (g_shell.errorno ? 0 : 1);
}

