/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:57:20 by modaouch          #+#    #+#             */
/*   Updated: 2019/07/04 18:19:03 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
		ft_putendl("---------------------------~ redir pipe2");
		return true;//(exec_redir_pipe(ast));//to_build
	}
	else if (is_other_exec(ast->token->tokind))
	{
		ft_printf("----------------------------~ other2 %d\n", ast->token->tokind);
		return (exec_cmd(ast, 0));//to finish
	}
	return (false);
}
