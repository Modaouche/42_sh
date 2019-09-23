/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:15:22 by araout            #+#    #+#             */
/*   Updated: 2019/09/23 12:27:02 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		io_file_cmp(t_ast_ptr *ast_head, t_ast *save,\
		t_token *lookahead)
{
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

void			io_file(t_edit *line_e)
{
	t_ast_ptr	*ast_head;
	t_ast		*save;
	t_token		*lookahead;

	ast_head = st_ast();
	save = ast_head->curr_head;
	if (token_cmp(last_token(0), T_GREAT, T_GREATAND, T_DGREAT,\
		T_CLOBBER, T_LESSGREAT, T_LESS, T_LESSAND, -1)\
		&& g_shell.errorno != ER_SYNTAX)
	{
		ast_right_insert(get_next_token(&(line_e->line),\
			&(line_e->ofst)));
		assign_to_word();
		if (token_cmp(last_token(0), T_WORD, -1))
		{
			lookahead = get_next_token(&(line_e->line), &(line_e->ofst));
			io_file_cmp(ast_head, save, lookahead);
		}
		else
			g_shell.errorno = ER_SYNTAX;
	}
}
