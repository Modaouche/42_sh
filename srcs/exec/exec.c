/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:57:20 by modaouch          #+#    #+#             */
/*   Updated: 2019/07/04 18:19:03 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ast_execution(t_ast *ast)
{
	if (!ast)
		return ;
	if (is_slice_exec(ast->token->tokind))
	{
		ft_putendl("-----------------[ slice ]");
		ast_execution(ast->left);
		ast_execution(ast->right);
	}
	else if (is_and_or_exec(ast->token->tokind))
		exec_and_or(ast);
	else if (is_redir_pipe_exec(ast->token->tokind))
	{
		ft_printf("-----------------[ redir pipe %d ]\n", ast->token->tokind);
//		exec_redir_pipe(ast);
	}
	else if (is_other_exec(ast->token->tokind))
	{
		ft_printf("-----------------[ other %d ]\n", ast->token->tokind);
		exec_cmd(ast, 0);
	}
}

void		line_execution(void)
{
	ft_putendl("\n----------------------------------Beginning-------------------------------");
	if (!g_shell.ast)
		return ;
	ast_execution(g_shell.ast);
	ast_free(&(g_shell.ast));
	ft_putendl("----------------------------------End-------------------------------");
}
