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

static int		line_parser_prime(t_edit *line_e)
{
	g_errorno = 0;
	if (!token_cmp(last_token(0), T_EOF, -1))
		complet_cmd(line_e);
	if (g_errorno == ER_SYNTAX)
		return (0);
	return (1);
}

int         line_parser(t_edit *line_e)
{
	t_ast_ptr	*ast_head;
	t_ast		*last;

	ast_head = st_ast();
	ast_head->curr_head = NULL;
	ast_left_insert(get_next_token(&(line_e->line), &(line_e->ofst)));
	if (line_parser_prime(line_e))
	{
		if (!(ast_head->root))
			ast_head->root = ast_head->curr_head;
		if (last_token(ast_head->root) != T_EOF)
			bind_last_head();
		infix_print_ast(ast_head->root);
		ft_putendl("");
		ast_head->curr_head = NULL;
	}
	else
	{
		last = last_node(ast_head->root);
		ft_printf_fd(2, "42sh: parse error near `%s'\n",\
				last->token->lexeme);
	}	
	ast_head->curr_head = NULL;//leaksdeoufff
	ast_head->root = NULL;//leaksdeoufff
	return (1);
}
