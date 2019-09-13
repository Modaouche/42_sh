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

static int 	ft_putendlr(char *s)
{
	ft_putendl(s);
	return (1);
}//to rm

static bool		ft_strcmp_ret(char *to_cmp, char *with, bool ret)
{
	if (ret != true && !ft_strcmp(to_cmp, with))
		return (true);
	return (false);
}

bool		is_builtin(t_ast *ast, char *bu)
{
	bool		ret;
	char		**argv;

	argv = NULL;
	if (!bu)
		argv = get_cmd(ast);
	bu = (!bu) ? argv[0] : bu;
	ret = false;
	(ft_strcmp_ret("set", bu, ret)) ? ret = ft_putendlr("is builtin") : 0;
	(ft_strcmp_ret("unset", bu, ret)) ? ret = ft_putendlr("is builtin") : 0;
	(ft_strcmp_ret("cd", bu, ret)) ? ret = ft_putendlr("is builtin") : 0;
	(ft_strcmp_ret("echo", bu, ret)) ? ret = ft_putendlr("is builtin") : 0;
	(ft_strcmp_ret("exit", bu, ret)) ? ret = ft_putendlr("is builtin") : 0;
	(ft_strcmp_ret("jobs", bu, ret)) ? ret = ft_putendlr("is builtin") : 0;
	(ft_strcmp_ret("fg", bu, ret)) ? ret = ft_putendlr("is builtin") : 0;
	(ft_strcmp_ret("bg", bu, ret)) ? ret = ft_putendlr("is builtin") : 0;
	if (!argv)
		free_tabstr(&argv);
	if (ret == 1)
		return (bu);
	return (NULL);
}

bool		exec_builtin(t_ast *ast)
{
	bool		ret;
	char		**argv;
	char		*bu;

	argv = get_cmd(ast);
	bu = argv[0];
	ret = 0;
	(ft_strcmp_ret("set", bu, ret)) ? ret = ft_putendlr("exec builtin") : 0;
	(ft_strcmp_ret("unset", bu, ret)) ? ret = ft_putendlr("exec builtin") : 0;
	(ft_strcmp_ret("cd", bu, ret)) ? ret = ft_putendlr("exec builtin") : 0;
	(ft_strcmp_ret("echo", bu, ret)) ? ret = ft_putendlr("exec builtin") : 0;
	(ft_strcmp_ret("exit", bu, ret)) ? ret = ft_putendlr("exec builtin") : 0;
	(ft_strcmp_ret("jobs", bu, ret)) ? ret = ft_putendlr("exec builtin") : 0;
	(ft_strcmp_ret("fg", bu, ret)) ? ret = ft_putendlr("exec builtin") : 0;
	(ft_strcmp_ret("bg", bu, ret)) ? ret = ft_putendlr("exec builtin") : 0;
	//ret = ret_set(bu) : 0;//tobuild VV
	//ret = ret_unset(bu) : 0;
	//ret = ret_cd(bu) : 0;
	//ret = ret_echo(bu) : 0;
	//ret = ret_exit(bu) : 0;
	//ret = ret_jobs(bu) : 0;
	//ret = ret_fg(bu) : 0;
	//ret = ret_bg(bu) : 0;//until here
	free_tabstr(&argv);
	g_shell.ret = ret;
	if (ret == 0)
		return (1);
	return (0);
}
