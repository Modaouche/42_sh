/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io_fct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 00:38:00 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 13:00:37 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		io_redirect_fct(t_edit *line_e)
{
	if (token_cmp(last_token(0), T_GREAT, T_GREATAND, T_DGREAT, T_IO_NB,\
		T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS, T_LESSAND,\
		T_DLESSDASH, -1) && g_shell.errorno != ER_SYNTAX)
	{
		io_number_opt_fct((line_e));
		io_kind_fct((line_e));
	}
}

void		io_number_opt_fct(t_edit *line_e)
{
	t_ast_ptr	*ast_head;
	t_ast		*save;
	t_token		*lookahead;

	ast_head = st_ast();
	save = ast_head->curr_head;
	if (token_cmp(last_token(0), T_IO_NB, -1) && g_shell.errorno != ER_SYNTAX)
	{
		lookahead = get_next_token(&(line_e->line), &(line_e->ofst));
		if (token_cmp(ast_head->curr_head->token->tokind, T_GREAT,\
			T_GREATAND, T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS,\
			T_DLESS, T_LESSAND, T_DLESSDASH, T_PIPE, T_AND_IF,\
			T_OR_IF, -1)\
			&& !token_cmp(lookahead->tokind, T_GREAT, T_GREATAND,\
			T_DGREAT, T_CLOBBER, T_LESSGREAT, T_LESS, T_DLESS,\
			T_LESSAND, T_DLESSDASH, T_PIPE, T_AND_IF, T_OR_IF, -1))
		{
			ast_head->curr_head = ast_head->curr_head->right;
			ast_left_insert(lookahead);
			save->right = ast_head->curr_head;
			ast_head->curr_head = save;
		}
		else
			ast_left_insert(lookahead);
	}
}

void		io_kind_fct(t_edit *line_e)
{
	if (token_cmp(last_token(0), T_GREAT, T_GREATAND, T_DGREAT,\
		T_CLOBBER, T_LESSGREAT, T_LESS, T_LESSAND, -1)\
		&& g_shell.errorno != ER_SYNTAX)
		io_file((line_e));
	else if (token_cmp(last_token(0), T_DLESSDASH, T_DLESS, -1)\
		&& g_shell.errorno != ER_SYNTAX)
		io_here((line_e));
	assign_to_word();
}
/*
**gerer les heredocd (voir la doc opengrp) et and , once the ctrl v + j set,
**go make a parser for \n.                  //c'est a revoir...
*/
