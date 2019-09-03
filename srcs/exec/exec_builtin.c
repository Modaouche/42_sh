/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:57:20 by modaouch          #+#    #+#             */
/*   Updated: 2019/07/04 18:19:03 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int 	ft_putendlr(char *s)
{
	ft_putendl(s);
	return (1);
}//to rm

char		*is_builtin(t_ast *ast)
{
	bool		ret;
	char		**argv;

	argv = get_cmd(ast);
	cmd = argv[0];
	ret = 0;
	(ft_strcmp_ret("set", cmd, ret)) ? ret = ft_putendlr("is builtin") : 0;
	(ft_strcmp_ret("unset", cmd, ret)) ? ret = ft_putendlr("is builtin") : 0;
	(ft_strcmp_ret("cd", cmd, ret)) ? ret = ft_putendlr("is builtin") : 0;
	(ft_strcmp_ret("echo", cmd, ret)) ? ret = ft_putendlr("is builtin") : 0;
	(ft_strcmp_ret("exit", cmd, ret)) ? ret = ft_putendlr("is builtin") : 0;
	(ft_strcmp_ret("jobs", cmd, ret)) ? ret = ft_putendlr("is builtin") : 0;
	(ft_strcmp_ret("fg", cmd, ret)) ? ret = ft_putendlr("is builtin") : 0;
	(ft_strcmp_ret("bg", cmd, ret)) ? ret = ft_putendlr("is builtin") : 0;
	free_tabstr(&argv);
	if (ret == 1)
		return (cmd);
	return (NULL);
}

bool		exec_builtin(char **argv)
{
	bool		ret;
	char		**argv;

	argv = get_cmd(ast);
	cmd = argv[0];
	ret = 0;
	(ft_strcmp_ret("set", cmd, ret)) ? ret = ft_putendlr("exec builtin") : 0;
	(ft_strcmp_ret("unset", cmd, ret)) ? ret = ft_putendlr("exec builtin") : 0;
	(ft_strcmp_ret("cd", cmd, ret)) ? ret = ft_putendlr("exec builtin") : 0;
	(ft_strcmp_ret("echo", cmd, ret)) ? ret = ft_putendlr("exec builtin") : 0;
	(ft_strcmp_ret("exit", cmd, ret)) ? ret = ft_putendlr("exec builtin") : 0;
	(ft_strcmp_ret("jobs", cmd, ret)) ? ret = ft_putendlr("exec builtin") : 0;
	(ft_strcmp_ret("fg", cmd, ret)) ? ret = ft_putendlr("exec builtin") : 0;
	(ft_strcmp_ret("bg", cmd, ret)) ? ret = ft_putendlr("exec builtin") : 0;
	//ret = ret_set(cmd) : 0;//tobuild VV
	//ret = ret_unset(cmd) : 0;
	//ret = ret_cd(cmd) : 0;
	//ret = ret_echo(cmd) : 0;
	//ret = ret_exit(cmd) : 0;
	//ret = ret_jobs(cmd) : 0;
	//ret = ret_fg(cmd) : 0;
	//ret = ret_bg(cmd) : 0;//until here
	free_tabstr(&argv);
	g_shell.ret = ret;
	if (ret == 0)
		return (1);
	return (0);
}
