/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:57:20 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 11:14:08 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
 	T_PIPE,      |  V
	T_LESS,      <  V
	T_LESSAND,   <& V 
	T_GREAT,     >  V
	T_GREATAND,  >& V
	T_DGREAT,    >> V
	T_LESSGREAT, <> ?
	T_CLOBBER,   >| ?
	T_DLESS,     << V
	T_DLESSDASH, <<-^

	debut :
		- ast rempli avec les redir et pipes
		- peut avoir des assign et/ou word in ast mais le debut = redir_pipe
		- t_job job = null
 * */

bool		exec_redir_pipe(t_ast *ast, t_job *job, bool is_root)
{
	char **args;
	char **assigns;

	ft_putendl("-----------------[ redir_pipe ]");
	if (!is_root && ast->left)
		exec_redir_pipe(ast->left, 0);
	if (!is_root && ast->right)
		exec_redir_pipe(ast->right, 0);
	assigns = get_assignments(ast);
	if (jobs && jobs->assigns)
		assigns = get_assigned_env(assigns, assigns);
	if (is_root)
	{
		push_back_job(ast, assigns);
		if (ast->left)
			exec_redir_pipe(ast->left, 0);
		if (ast->right)
			exec_redir_pipe(ast->righ,0);
		g_shell.errorno = NO_ERROR;
		if (args)
		launch_job(last_job());
	}
	/* all ok*/

	if (g_shell.errorno)
	{
		remove_completed_job(&g_shell.first_job);
		error_msg("./42sh");
	}
	return (g_shell.errorno ? 0 : 1);
}

bool		exec_and_or(t_ast *ast)
{
	if (ast->token->tokind == T_EOF)
		return (exec_and_or(ast->left));
	if (ast->token->tokind == T_AND_IF)
	{
		ft_putendl("---------------------------~ and");
		if (exec_and_or(ast->left) && exec_and_or(ast->right))
			return (true);
	}
	else if (ast->token->tokind == T_OR_IF)
	{
		ft_putendl("---------------------------~ or");
		if (exec_and_or(ast->left) || exec_and_or(ast->right))
			return (true);
	}
	else if (is_redir_pipe_exec(ast->token->tokind))//add eof tokentocmp
	{
		return (exec_redir_pipe(ast, true));//to_build
	}
	else if (is_other_exec(ast->token->tokind))
	{
		ft_printf("-------------------------~ other2 %d\n", ast->token->tokind);
		return (exec_cmd(ast, 0));//to finish
	}
	return (false);
}
