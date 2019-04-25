/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 14:03:19 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/12 02:53:08 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int			line_parser(t_ast **ast, t_edit *line_e)//maybe useless
{
	g_errorno = 0;
	ast_insert_left(get_next_token(&(line_e->line), &(line_e->i)) , ast);
	complet_cmd(ast, line_e);
	if (g_errorno == ER_SYNTAX)//to change maybe
		return (0);
	return (1);
}

int line_lexer(t_edit *line_e)
{
	t_ast	*ast;

	ast = NULL;
    line_edition(line_e);
	ft_putendl("");
	if (line_parser(&ast, line_e) == 1)
		infix_print_ast(ast);
	else//maybe useless
		ft_putstr_fd("42sh syntax error.0\n", 2);//maybe useless
    return (1);
}
