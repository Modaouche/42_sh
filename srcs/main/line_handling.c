/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 12:16:34 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 01:50:01 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		line_parser(t_ast **ast, t_edit *line_e)
{
	g_errorno = 0;
	ast_left_insert(get_next_token(&(line_e->line), &(line_e->ofst)), ast);
	if (!token_cmp(head_of_line(*ast), T_EOF, -1))
		complet_cmd(ast, line_e);
	if (g_errorno == ER_SYNTAX)
		return (0);
	return (1);
}

int         line_lexer(t_edit *line_e)
{
	t_ast_ptr	*ast_head;

	ast_head = st_ast();
	ast_head->root = NULL;
	ast_head->curr_head = NULL;
	if (line_parser(&(ast_head->curr_head), line_e) == 1)
	{
		if (!(ast_head->root))
			ast_head->root = ast_head->curr_head;
		infix_print_ast(ast_head->root);
	}
	else //useless because we need to print specified error when we find it
		ft_putstr_fd("42sh syntax error\n", 2);
	return (1);
}
