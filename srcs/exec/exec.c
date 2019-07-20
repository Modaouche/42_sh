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
		ft_putendl("                           -- slice");
		ast_execution(ast->left);
	}
	if (is_slice_exec(ast->token->tokind))
	{
		ft_putendl("                           -- slice2");
		ast_execution(ast->right);
	}
	else if (is_and_or_exec(ast->token->tokind))
		exec_and_or(ast);
	else if (is_redir_pipe_exec(ast->token->tokind))
		ft_putendl("                           -- redir pipe");//		exec_redirec(ast);//tobuild
	else if (is_other_exec(ast->token->tokind))
	{
		ft_printf("                           -- other %d\n", ast->token->tokind);
		exec_cmd(ast);
	}
}

void		line_execution(void)
{
	ft_putendl("----------------------------------Beginning-------------------------------");
	if (!g_shell.ast)
		return ;
	ast_execution(g_shell.ast);
	//ast_free(g_shell.ast);to build
	g_shell.ast = NULL;//leaks to remove use the fct above
//	ft_putendl("Comming Soon ;)");
	ft_putendl("----------------------------------End-------------------------------");
}
