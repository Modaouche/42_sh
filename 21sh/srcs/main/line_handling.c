/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 12:16:34 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 09:20:33 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		line_parser_prime(t_edit *line_e)
{
	g_shell.errorno = 0;
	ast_left_insert(get_next_token(&(line_e->line), &(line_e->ofst)));
	if (!token_cmp(last_token(0), T_EOF, -1))
		complet_cmd(line_e);
	if (g_shell.errorno == ER_SYNTAX)
		return (0);
	return (1);
}

void			line_parser(t_edit *line_e)
{
	t_ast_ptr	*ast_head;
	t_ast		*last;

	ast_head = st_ast();
	ast_head->curr_head = NULL;
	ast_head->root = NULL;
	if (line_parser_prime(line_e))
	{
		if (!(ast_head->root))
			ast_head->root = ast_head->curr_head;
		if (last_token(ast_head->root) != T_EOF)
			bind_last_head();
		ast_head->curr_head = NULL;
		g_shell.ast = ast_head->root;
		infix_print_ast(g_shell.ast);
	}
	else
	{
		(!(ast_head->root)) ? ast_head->root = ast_head->curr_head : 0;
		last = last_node(ast_head->root);
		ft_printf_fd(2, "21sh : parse error near `%s'\n",
				last->token->lexeme);
		ast_free(&(ast_head->root));
	}
}
