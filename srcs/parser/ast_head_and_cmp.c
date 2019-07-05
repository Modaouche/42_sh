/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_last_and_cmp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 06:59:16 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 11:25:11 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "shell.h"

bool	token_cmp(int kind, ...)
{
	va_list tokens;
	int current_token;

	va_start(tokens, kind);
	while ((current_token = va_arg(tokens, int)) != -1)
	{
		if (current_token == kind)
		{
			va_end(tokens);
			return (TRUE);
		}
	}
	va_end(tokens);
	return (FALSE);
}

int	last_token(t_ast *ast)
{
	t_ast_ptr *ast_head;

	if (!ast)
	{	
		ast_head = st_ast();
		if (!(ast = ast_head->curr_head))
			return (0);
	}
	if (ast->right)
		return (last_token(ast->right));
	if (!ast->right)
		return (ast->token->tokind);
	return (0);
}

t_ast	*last_node(t_ast *ast)
{
	t_ast_ptr *ast_head;

	if (!ast)
	{	
		ast_head = st_ast();
		if (!(ast = ast_head->curr_head))
			return (0);
	}
	if (ast->right)
		return (last_node(ast->right));	
	if (!ast->right)
		return (ast);
	return (0);
}

void	bind_last_head(void)
{
	t_ast_ptr	*ast_head;
	t_ast		*last;

	ast_head = st_ast();
	last = ast_head->root;
	while(last->right && last->right->right)
		last = last->right;
	last->right = ast_head->curr_head;
}//check if it's ok 
