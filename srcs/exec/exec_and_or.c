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

bool		exec_and_or(t_ast *ast)
{
	if (ast->token->tokind == T_EOF)
		return (exec_and_or(ast->left));
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
	else if (is_redir_exec(ast->token->tokind)\
			|| ast->token->tokind == T_PIPE)
		return (exec_cmd(ast, true));
	else if (is_other_exec(ast->token->tokind))
		return (exec_cmd(ast, false));
	return (false);
}
