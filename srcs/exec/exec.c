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
	if (!ast || ast->token->tokind == T_EOF)
		return ;
	if (is_slice_exec(ast->token->tokind))
		ast_execution(ast->left);
	if (is_slice_exec(ast->token->tokind))
		ast_execution(ast->right);
	else if (is_and_or_exec(ast->token->tokind))
		exec_and_or(ast);
	//else if (is_redir_pipe_exec(ast->token->tokind))
	//	exec_redirec(ast);//tobuild
}

void		line_execution(void)
{
	if (!g_shell.ast)
		return ;
	ast_execution(g_shell.ast);
	//ast_free(g_shell.ast);to build
	g_shell.ast = NULL;//leaks to remove use fct above
	ft_putendl("Coming Soon ;)");
}
