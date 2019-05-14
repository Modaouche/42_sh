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

#include "../includes/shell.h"

int			line_parser(t_ast **ast, t_edit *line_e)
{
		g_errorno = 0;
		ast_insert_left(get_next_token((const char **)&(line_e->line), &(line_e->ofst)), ast);
		if (!first_set(head_of_line(*ast), T_EOF, -1))
				complet_cmd(ast, line_e);
		if (g_errorno == ER_SYNTAX)//to change maybe
				return (0);
		return (1);
}

int         line_lexer(t_edit *line_e)
{
		t_ast	*ast;

		ast = NULL;
		if (line_parser(&ast, line_e) == 1)
				infix_print_ast(ast);
		else//maybe useless
				ft_putstr_fd("42sh syntax error.0\n", 2);//maybe useless
    return (1);
}