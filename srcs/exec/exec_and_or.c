/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_or.c                                       :+:      :+:    :+:   */
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
	if (ast->token->tokind == T_AND_IF)
	{
		if (exec_and_or(ast->left) && exec_and_or(ast->right))
			return (true);
	}
	else if (ast->token->tokind == T_OR_IF)
	{
		if (exec_and_or(ast->left) || exec_and_or(ast->right))		
			return (true);
	}
	else if (is_redir_pipe_exec(ast->token->tokind))
	{
//		if (exec_redir(ast))//to_build
//			return (true);
	}
	//else
		//if (exec_cmd(ast))//to finish
		//	return (true);
	return (false);
}
