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

	ret = ft_built_in(args);
	ft_free_tab(args);
	g_shell.ret = ret;
	return (ret == 0);
}

int			apply_local_assignments(t_ast *ast)
{
	char			**assignments;
	unsigned int	i;
	int				c;
	
	if (!(assignments = get_assignments(ast)))
		return (1);
	i = 0;
	while (assignments[i])
	{
		if ((c = ft_cfind(assignments[i], '=')) > 0)
		{
			assignments[i][c] = '\0';
			g_shell.intern_var = set_var_env(assignments[i],\
                    &assignments[i][c + 1], g_shell.intern_var);
		}
		ft_strdel(&assignments[i]);
		++i;
	}
	ft_free_tab(assignments);
	return (0);
}

bool		exec_cmd(t_ast *ast, bool to_fork)
{
	char **args;

    args = get_cmd(ast);
    if (args && !to_fork && is_builtin(args[0]))
	    return (exec_builtin(args));
	if (!args)
		return (apply_local_assignments(ast));
	ft_free_tab(args);
	g_shell.errorno = NO_ERROR;
	push_back_job(ast);
	if (!g_shell.errorno)
		launch_job(last_job());
	if (g_shell.errorno)
	{
		remove_completed_job(&g_shell.first_job);
		error_msg("./42sh");
	}
	return (g_shell.errorno ? 0 : 1);
}
